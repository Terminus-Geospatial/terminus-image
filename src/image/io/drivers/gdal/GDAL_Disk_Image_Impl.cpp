/**
 * @file    GDAL_Disk_Image_Impl.cpp
 * @author  Marvin Smith
 * @date    7/15/2023
*/
#include "GDAL_Disk_Image_Impl.hpp"

/// Terminus Libraries
#include "GDAL_Utilities.hpp"

/// External Terminus Libraries
#include <terminus/outcome/Result.hpp>

/// C++ Libraries
#include <mutex>


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

    /// Create the GDAL Dataset
    m_read_dataset.reset( (GDALDataset*)GDALOpen( pathname.native().c_str(), GA_ReadOnly ), GDAL_Deleter_Null_Okay );

    // Make sure it opens okay
    if( !m_read_dataset )
    {
        std::stringstream sout;
        sout << "GDAL: Failed to open dataset " << m_pathname.native();
        logger.warn( sout.str() );
        return outcome::fail( error::ErrorCode::FILE_IO_ERROR,
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

        std::stringstream sout;
        for( int i=0; i<CSLCount( metadata ); i++ )
        {
            sout << "\t\t" << CSLGetField( metadata, i ) << std::endl;
        }
        logger.trace( sout.str() );

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
            sout << "   - " << i << " -> " << GDALGetColorInterpretationName( channel_codes[i] ) << std::endl;
        }
        sout << "Will attempt to determine by simple channel counts.";

        logger.error( sout.str() );

        // Check next set of rules
        if( channel_codes.size() == 1 )
        {
            m_format.set_pixel_format( Pixel_Format_Enum::GRAY );
            m_format.set_planes( 1 );
        }
        else if( channel_codes.size() == 2 )
        {
            m_format.set_pixel_format( Pixel_Format_Enum::GRAYA );
            m_format.set_planes( 1 );
        }
        else if( channel_codes.size() == 3 )
        {
            m_format.set_pixel_format( Pixel_Format_Enum::RGB );
            m_format.set_planes( 1 );
        }
        else if( channel_codes.size() == 4 )
        {
            m_format.set_pixel_format( Pixel_Format_Enum::RGBA );
            m_format.set_planes( 1 );
        }
        else
        {
            m_format.set_pixel_format( Pixel_Format_Enum::SCALAR );
            m_format.set_planes( channel_codes.size() );
        }
    }
    else
    {
        m_format.set_pixel_format( pix_res.value() );
        m_format.set_planes( 1 );
    }

    /// Skip color palettes for now

    // Get the block size
    m_blocksize = default_block_size();
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
        return outcome::fail( error::ErrorCode::UNINITIALIZED,
                              "GDAL:  No dataset opened." );
    }
}

}