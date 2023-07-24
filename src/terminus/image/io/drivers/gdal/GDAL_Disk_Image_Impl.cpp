/**
 * @file    GDAL_Disk_Image_Impl.cpp
 * @author  Marvin Smith
 * @date    7/15/2023
*/
#include "GDAL_Disk_Image_Impl.hpp"

/// Terminus Libraries
#include "../../../pixel/convert.hpp"
#include "GDAL_Utilities.hpp"

/// External Terminus Libraries
#include <terminus/log/utility.hpp>
#include <terminus/outcome/Result.hpp>

/// C++ Libraries
#include <mutex>

// GDAL Libraries
#include <gdal.h>


namespace tmns::image::io::gdal {

/********************************/
/*          Constructor         */
/********************************/
GDAL_Disk_Image_Impl::GDAL_Disk_Image_Impl( const std::filesystem::path& pathname,
                                            const ColorCodeLookupT&      color_reference_lut )
  : m_pathname( pathname ),
    m_color_reference_lut( color_reference_lut )
{
    open( m_pathname );
}

/************************************/
/*          Open the Dataset        */
/************************************/
ImageResult<void> GDAL_Disk_Image_Impl::open( const std::filesystem::path& pathname )
{
    // Lock the global GDAL Context
    std::unique_lock<std::mutex> lck( get_master_gdal_mutex() );
    auto logger = get_master_gdal_logger();
    logger.trace( "Opening dataset for file: ", pathname.native() );

    /// Create the GDAL Dataset
    m_read_dataset.reset( (GDALDataset*)GDALOpen( pathname.native().c_str(), GA_ReadOnly ), GDAL_Deleter_Null_Okay );

    // Make sure it opens okay
    if( !m_read_dataset )
    {
        std::stringstream sout;
        sout << "GDAL: Failed to open dataset " << m_pathname.native();
        logger.warn( sout.str() );
        return outcome::fail( core::error::ErrorCode::FILE_IO_ERROR,
                               sout.str() );
    }

    // Given dataset, get some information
    std::shared_ptr<GDALDataset> dataset( get_dataset_ptr().value() );

    m_pathname = pathname;
    m_format.set_cols( dataset->GetRasterXSize() );
    m_format.set_rows( dataset->GetRasterYSize() );

    // Log the metadata information
    {
        logger.trace( "Metadata Description: ", dataset->GetDescription() );

        char** metadata = dataset->GetMetadata();
        logger.trace( "Count: ", CSLCount(metadata) );

        if( CSLCount(metadata) > 0 )
        {
            std::stringstream sout;
            for( int i=0; i<CSLCount( metadata ); i++ )
            {
                sout << "\t\t" << CSLGetField( metadata, i ) << std::endl;
            }
            logger.trace( sout.str() );
        }

        logger.trace( "Driver: ", dataset->GetDriver()->GetDescription(),
                      ", ", dataset->GetDriver()->GetMetadataItem( GDAL_DMD_LONGNAME ) );

        logger.trace( "Image Size: ", dataset->GetRasterXSize(), " cols, ",
                      dataset->GetRasterYSize(), " rows, ", dataset->GetRasterCount(),
                      " channels" );

    }

    /**
     * Figure out which pixel format to use from the band composition.  This is oddly difficult,
     * so I'm going to start initially with an lookup table and just add as I go.
     */
    std::vector<int> channel_codes;

    for( int i=1; i<= dataset->GetRasterCount(); ++i )
    {
        channel_codes.push_back( dataset->GetRasterBand(i)->GetColorInterpretation() );
    }

    // Match against expected patterns
    bool match_found = false;

    // Add match logic here
    auto pix_res = gdal_driver_to_pixel_type( m_color_reference_lut,
                                              channel_codes );
    if( pix_res.has_error() )
    {
        std::stringstream sout;
        sout << "Unable to determine pixel-type from color-codes.  Check the lookup table.\n";
        sout << " - Actual Values:" << std::endl;
        for( size_t i=0; i<channel_codes.size(); i++ )
        {
            sout << "   - " << i << " -> " << GDALGetColorInterpretationName( (GDALColorInterp)channel_codes[i] ) << std::endl;
        }
        sout << "Will attempt to determine by simple channel counts.";

        logger.error( sout.str() );

        // Check next set of rules
        if( channel_codes.size() == 1 )
        {
            m_format.set_pixel_type( Pixel_Format_Enum::GRAY );
            m_format.set_planes( 1 );
        }
        else if( channel_codes.size() == 2 )
        {
            m_format.set_pixel_type( Pixel_Format_Enum::GRAYA );
            m_format.set_planes( 1 );
        }
        else if( channel_codes.size() == 3 )
        {
            m_format.set_pixel_type( Pixel_Format_Enum::RGB );
            m_format.set_planes( 1 );
        }
        else if( channel_codes.size() == 4 )
        {
            m_format.set_pixel_type( Pixel_Format_Enum::RGBA );
            m_format.set_planes( 1 );
        }
        else
        {
            m_format.set_pixel_type( Pixel_Format_Enum::SCALAR );
            m_format.set_planes( channel_codes.size() );
        }

    }
    else
    {
        m_format.set_pixel_type( pix_res.value() );
        m_format.set_planes( 1 );
    }

    /// Get the channel-type
    auto ctype = gdal_pixel_format_to_channel_type( dataset->GetRasterBand(1)->GetRasterDataType() );
    if( ctype.has_error() )
    {
        get_master_gdal_logger().error( "Unable to parse channel-type. ", ctype.error().message() );
        return outcome::fail( ctype.error() );
    }
    m_format.set_channel_type( ctype.value() );

    // Color Palette (if supported)
    if( dataset->GetRasterCount() == 1 &&
        dataset->GetRasterBand(1)->GetColorInterpretation() == GCI_PaletteIndex )
    {
        // Setup the pixel and plane info
        m_format.set_pixel_type( Pixel_Format_Enum::RGBA );
        m_format.set_planes( 1 );

        // Fetch the color table and add to table
        GDALColorTable* color_table = dataset->GetRasterBand(1)->GetColorTable();

        m_color_table.resize( color_table->GetColorEntryCount() );
        GDALColorEntry color;
        for( size_t i=0; i<m_color_table.size(); i++ )
        {
            color_table->GetColorEntryAsRGB( i, &color );
            m_color_table[i] = PixelRGBA_u8( color.c1, color.c2, color.c3, color.c4 );
        }
    }

    // Get the block size
    m_blocksize = default_block_size();

    return outcome::ok();
}

/********************************************/
/*          Read memory from disk           */
/********************************************/
ImageResult<void> GDAL_Disk_Image_Impl::read( const Image_Buffer&         dest,
                                              const math::Rectangle<int>& bbox,
                                              bool                        rescale ) const
{
    // Perform bounds checks
    if( !format().bbox().is_inside( bbox ) )
    {
        return outcome::fail( core::error::ErrorCode::OUT_OF_BOUNDS,
                              "Bounding box outside the bounds of the image. ",
                              format().bbox().to_string(),
                              ", Requested: " + bbox.to_string() );
    }

    // Create source fetching region
    Image_Format src_fmt = format();
    src_fmt.set_cols( bbox.width() );
    src_fmt.set_rows( bbox.height() );

    tmns::log::error( src_fmt.To_Log_String() );

    std::shared_ptr<uint8_t> src_data(new uint8_t[ src_fmt.raster_size_bytes() ]);
    Image_Buffer src(src_fmt, src_data.get());

    {
        std::unique_lock<std::mutex> lck( get_master_gdal_mutex() );

        auto dataset = get_dataset_ptr().value();

        auto& logger = get_master_gdal_logger();

        auto ch_size = channel_size_bytes( src.format().channel_type() ).value();
        if( m_color_table.empty() )
        {
            auto nchannels = num_channels( format().pixel_type() ).value();
            for( size_t p = 0; p < format().planes();   ++p ) {
            for( size_t c = 0; c < nchannels; ++c )
            {
                // Only one of channels() or planes() will be nonzero.
                auto* band = dataset->GetRasterBand( c + p + 1 );

                auto gdal_pix_fmt = channel_type_to_gdal_pixel_format( format().channel_type() ).value();
                CPLErr result = band->RasterIO( GF_Read,
                                                bbox.min().x(),
                                                bbox.min().y(),
                                                bbox.width(),
                                                bbox.height(),
                                                ( uint8_t* ) src( 0, 0, p ) + ch_size * c,
                                                src.format().cols(),
                                                src.format().rows(),
                                                gdal_pix_fmt,
                                                src.cstride(),
                                                src.rstride() );
                if( result != CE_None )
                {
                    logger.warn( "RasterIO problem: ",
                                 CPLGetLastErrorMsg() );
                }
            }}
        }

        // Convert the color table
        else
        {
            GDALRasterBand* band = dataset->GetRasterBand(1);
            uint8_t* index_data = new uint8_t[ bbox.width() * bbox.height() ];
            CPLErr result = band->RasterIO( GF_Read, bbox.min().x(), bbox.min().y(), bbox.width(), bbox.height(),
                                           index_data, bbox.width(), bbox.height(), GDT_Byte, 1, bbox.width() );
            if (result != CE_None)
            {
                logger.warn( "RasterIO problem: ",
                                 CPLGetLastErrorMsg() );
            }


            PixelRGBA_u8* rgba_data = (PixelRGBA_u8*) src.data();
            for( int i=0; i<bbox.width()*bbox.height(); ++i )
            {
                rgba_data[i] = m_color_table[index_data[i]];
            }

            delete [] index_data;
        }
    }

    return convert( dest, src, rescale );
}

/************************************************/
/*          Print to log-friendly string        */
/************************************************/
std::string GDAL_Disk_Image_Impl::To_Log_String( size_t offset ) const
{
    std::string gap( offset, ' ' );
    std::stringstream sout;
    sout << gap << "   - pathname: " << m_pathname << std::endl;
    sout << gap << "   - read dataset set : " << std::boolalpha << (m_read_dataset != 0) << std::endl;
    sout << gap << "   - write dataset set: " << std::boolalpha << (m_write_dataset != 0) << std::endl;
    sout << m_format.To_Log_String( offset + 2 );
    sout << gap << "   - Block Size: " << m_blocksize.to_string() << std::endl;
    sout << gap << "   - Color Table Size: " << m_color_table.size() << std::endl;
    return sout.str();
}

/********************************************/
/*          Get the Format Structure        */
/********************************************/
Image_Format GDAL_Disk_Image_Impl::format() const
{
    return m_format;
}

/************************************************************/
/*          Get the pointer to the underlying dataset       */
/************************************************************/
ImageResult<GDAL_Disk_Image_Impl::DatasetPtrT> GDAL_Disk_Image_Impl::get_dataset_ptr() const
{
    if( m_write_dataset )
    {
        return outcome::ok<DatasetPtrT>( m_write_dataset );
    }
    else if( m_read_dataset )
    {
        return outcome::ok<DatasetPtrT>( m_read_dataset );
    }
    else
    {
        return outcome::fail( core::error::ErrorCode::UNINITIALIZED,
                              "GDAL:  No dataset opened." );
    }
}

/************************************************/
/*          Get the default block size          */
/************************************************/
math::Vector2i GDAL_Disk_Image_Impl::default_block_size() const
{
    auto dataset = get_dataset_ptr().value();

    GDALRasterBand *band = dataset->GetRasterBand(1);
    int xsize, ysize;
    band->GetBlockSize( &xsize, &ysize );

    // GDAL assumes a single-row stripsize even for file formats like PNG for
    // which it does not support true strip access. If it looks like it did
    // that (single-line block) only trust it if it's on the whitelist.
    if( ysize == 1 && !blocksize_whitelist( dataset->GetDriver() ) )
    {
        xsize = format().cols();
        ysize = format().rows();
    }

    return std::move( math::Vector2i( { xsize, ysize } ) );
}

/************************************************************************************/
/*          Get the list of supported/trusted drivers that rely on blocksizes       */
/************************************************************************************/
bool GDAL_Disk_Image_Impl::blocksize_whitelist( const GDALDriver* driver )
{
    // These drivers are mostly known to report good data
    static const size_t DRIVER_COUNT = 4;
    static const char drivers[DRIVER_COUNT][7] = {"GTiff", "ISIS3", "JP2ECW", "JP2KAK"};

    for (size_t i = 0; i < DRIVER_COUNT; ++i)
    {
        if (driver == GetGDALDriverManager()->GetDriverByName(drivers[i]))
        {
            return true;
        }
    }
    return false;
}

}