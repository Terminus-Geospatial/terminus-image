/**
 * @file    Image_Resource_Disk_NITF_Factory.cpp
 * @author  Marvin Smith
 * @date    7/19/2024
*/
#include <terminus/image/io/drivers/nitf/Image_Resource_Disk_NITF_Factory.hpp>

// C++ Libraries
#include <algorithm>

// Terminus Libraries
#include <terminus/log/utility.hpp>

namespace tmns::image::io::nitf {

/********************************************************/
/*          Check if image type is supported            */
/********************************************************/
bool Image_Resource_Disk_NITF_Factory::is_read_image_supported( const std::filesystem::path& pathname ) const
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

/********************************************************/
/*          Check if image type is supported            */
/********************************************************/
bool Image_Resource_Disk_NITF_Factory::is_write_image_supported( const std::filesystem::path& pathname ) const
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

    return false;
}

/************************************************/
/*          Create a new resource object        */
/************************************************/
Result<Image_Resource_Base::ptr_t>
        Image_Resource_Disk_NITF_Factory::create_read_driver( const std::filesystem::path& pathname ) const
{
    auto result = Image_Resource_Disk_NITF::create( pathname );
    if( result.has_error() )
    {
        return outcome::fail( result.assume_error() );
    }

    auto result_ptr = std::dynamic_pointer_cast<Image_Resource_Base>( result.assume_value() );
    return outcome::ok<Image_Resource_Base::ptr_t>( result_ptr );
}

/************************************************/
/*          Create a new resource object        */
/************************************************/
Result<Image_Resource_Base::ptr_t>
        Image_Resource_Disk_NITF_Factory::create_write_driver( const std::filesystem::path&             pathname,
                                                               const Image_Format&                      output_format,
                                                               const std::map<std::string,std::string>& write_options,
                                                               const math::Size2i&                      block_size ) const
{
    auto result = Image_Resource_Disk_NITF::create( pathname,
                                                    output_format,
                                                    write_options,
                                                    block_size );
    if( result.has_error() )
    {
        return outcome::fail( result.assume_error() );
    }

    auto result_ptr = std::dynamic_pointer_cast<Image_Resource_Base>( result.assume_value() );
    return outcome::ok<Image_Resource_Base::ptr_t>( result_ptr );
}

} // end of tmns::image::io::nitf namespace