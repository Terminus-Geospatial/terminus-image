/**
 * @file    Image_IO.hpp
 * @author  Marvin Smith
 * @date    7/10/2023
*/
#pragma once

// Terminus Libraries
#include "../error/ErrorCode.hpp"
#include "../image/Image_Base.hpp"

// C++ Libraries
#include <filesystem>

namespace tmns::warp::io {

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
error::Result<Image<PixelT>> Read_Image( const std::filesystem::path& pathname );
{
    tmns::log::info( "Loading image: ", pathname.string() );

    // Create an image resource for the data

    return error::ok();
}

} // End of tmns::warp::io namespace