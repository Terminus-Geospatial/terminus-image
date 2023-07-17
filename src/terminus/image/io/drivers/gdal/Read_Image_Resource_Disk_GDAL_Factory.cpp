/**
 * @file    Read_Image_Resource_Disk_GDAL_Factory.cpp
 * @author  Marvin Smith
 * @date    7/14/2023
*/
#include "Read_Image_Resource_Disk_GDAL_Factory.hpp"

// C++ Libraries
#include <algorithm>

namespace tmns::image::io::gdal {

/********************************************************/
/*          Check if image type is supported            */
/********************************************************/
bool Read_Image_Resource_Disk_GDAL_Factory::is_image_supported( const std::filesystem::path& pathname ) const
{
    // Check if file exists
    if( std::filesystem::exists( pathname ) )
    {
        // Get the extension
        auto ext = pathname.extension();
        if( std::find( m_supported_extensions.begin(),
                       m_supported_extensions.end(),
                       ext.native() )
            != m_supported_extensions.end() )
        {
            return true;
        }
    }
    return false;
}

/************************************************/
/*          Create a new resource object        */
/************************************************/
ImageResult<Read_Image_Resource_Base::ptr_t>
        Read_Image_Resource_Disk_GDAL_Factory::create( const std::filesystem::path& pathname ) const
{
    auto result = Read_Image_Resource_Disk_GDAL::create( pathname );
    if( result.has_error() )
    {
        return outcome::fail( result.assume_error() );
    }

    auto result_ptr = std::dynamic_pointer_cast<Read_Image_Resource_Base>( result.assume_value() );
    return outcome::ok<Read_Image_Resource_Base::ptr_t>( result_ptr );
}

} // end of tmns::image::io::gdal namespace