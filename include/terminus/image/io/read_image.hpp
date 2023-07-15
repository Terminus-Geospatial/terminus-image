/**
 * @file    Image_IO.hpp
 * @author  Marvin Smith
 * @date    7/10/2023
*/
#pragma once

// External Terminus Libraries
#include <terminus/outcome/Result.hpp>

// Terminus Libraries
#include "../error/ErrorCategory.hpp"
#include "../Image_Memory.hpp"
#include "drivers/Disk_Driver_Manager.hpp"
#include "drivers/Memory_Driver_Manager.hpp"
#include "Read_Image_Resource_Disk.hpp"
#include "read_image_from_resource.hpp"

// C++ Libraries
#include <filesystem>

namespace tmns::image::io {

/**
 * Load an image from disk
 *
 * @param[in] pathname Image to load
 * @param[out] image Image after loading.
 *
 * @return Status of the operation
 *
 * Note the image has to be returned as we are using
*/
template <typename PixelT>
ImageResult<Image_Memory<PixelT>> read_image( const std::filesystem::path&      pathname,
                                              const Disk_Driver_Manager::ptr_t  driver_manager = Disk_Driver_Manager::create_read_defaults() )
{
    tmns::log::info( "Loading image: ", pathname.string() );

    // Create an image resource for the data
    auto driver_res = driver_manager->pick_read_driver( pathname );

    if( driver_res.has_error() )
    {
        return outcome::fail( driver_res.assume_error() );
    }
    auto image_resource = driver_res.assume_value();

    auto read_result = read_image_from_resource<PixelT>( image_resource );
    if( read_result.has_error() )
    {
        return read_result.error();
    }
    return outcome::ok<Image_Memory<PixelT>>( std::move( read_result.value() ) );
}

} // End of tmns::image::io namespace