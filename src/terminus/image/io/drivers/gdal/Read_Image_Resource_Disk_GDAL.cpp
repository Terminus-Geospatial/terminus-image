/**
 * @file    Read_Image_Resource_Disk_GDAL.cpp
 * @author  Marvin Smith
 * @date    7/15/2023
*/
#include "Read_Image_Resource_Disk_GDAL.hpp"

// Terminus Libraries
#include "GDAL_Disk_Image_Impl.hpp"

namespace tmns::image::io::gdal {

/********************************/
/*          Constructor         */
/********************************/
Read_Image_Resource_Disk_GDAL::Read_Image_Resource_Disk_GDAL( const std::filesystem::path& pathname,
                                                              const ColorCodeLookupT&      color_reference_lut )
  : Read_Image_Resource_Disk( pathname ),
    m_color_reference_lut( color_reference_lut )
{
    m_impl = std::make_shared<GDAL_Disk_Image_Impl>( pathname,
                                                     color_reference_lut );
}

/********************************/
/*          Destructor          */
/********************************/
Read_Image_Resource_Disk_GDAL::~Read_Image_Resource_Disk_GDAL()
{
    m_impl.reset();
}

/****************************************************/
/*          Create Resource and Open Image          */
/****************************************************/
ImageResult<Read_Image_Resource_Disk_GDAL::ParentPtrT>
        Read_Image_Resource_Disk_GDAL::create( const std::filesystem::path& pathname )
{
    auto driver = std::make_shared<Read_Image_Resource_Disk_GDAL>( pathname );

    return outcome::ok<ParentPtrT>( driver );
}

/************************************/
/*          Open the dataset        */
/************************************/
ImageResult<void> Read_Image_Resource_Disk_GDAL::open( const std::filesystem::path& pathname )
{
    return m_impl->open( pathname );
}

/****************************************************/
/*          Read the image buffer from disk         */
/****************************************************/
ImageResult<void> Read_Image_Resource_Disk_GDAL::read( const Image_Buffer& dest,
                                                       const math::Rect2i& bbox ) const
{
    return m_impl->read( dest, bbox, m_rescale );

}

/****************************************/
/*          Get Format Object           */
/****************************************/
Image_Format Read_Image_Resource_Disk_GDAL::format() const
{
    return m_impl->format();
}

/************************************************/
/*          Print to log-friendly string        */
/************************************************/
std::string Read_Image_Resource_Disk_GDAL::To_Log_String( size_t offset ) const
{
    std::string gap( offset, ' ' );
    std::stringstream sout;
    sout << gap << " - Read_Image_Resource_Disk_GDAL" << std::endl;
    sout << gap << "   - Impl Initialized: " << std::boolalpha << (m_impl != 0) << std::endl;
    if( m_impl )
    {
        sout << m_impl->To_Log_String( offset );
    }
    return sout.str();
}

} // end of tmns::image::io::gdal namespace