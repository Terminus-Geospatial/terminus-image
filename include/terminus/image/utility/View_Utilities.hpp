/**
 * @file    View_Utilities.hpp
 * @author  Marvin Smith
 * @date    7/10/2023
*/
#pragma once

// Terminus Image Libraries
#include "../operations/pixel_cast.hpp"
#include "../types/Image_Base.hpp"
#include "../types/Image_Buffer.hpp"
#include "../types/Image_Memory.hpp"

// Terminus Libraries
#include <terminus/core/error/ErrorCategory.hpp>

namespace tmns::image::utility {

/**
 * Render the actual scene.
*/
ImageResult<void> visualize( const std::string&  window_name,
                             const Image_Buffer& buffer_data,
                             int                 window_sleep = 0 );

/**
 * Simple test tool for viewing an image
*/
template <typename PixelT>
ImageResult<void> view_image( const std::string&          window_name,
                              const Image_Memory<PixelT>& image,
                              int                         window_sleep = 0 )
{
    // We need all images to be uint8
    typedef typename Compound_Channel_Cast<PixelT,uint8_t>::type DestPixelT;
    //Image_Memory<DestPixelT> temp = ops::pixel_cast_rescale<DestPixelT>( image );
    return visualize( window_name,
                      image.buffer(),
                      window_sleep );
}

/**
 * View any image
*/
template <typename ImageType>
ImageResult<void> view_image( const std::string&  window_name,
                              const ImageType&    image,
                              int                 window_sleep = 0 )
{
    tmns::log::info( ADD_CURRENT_LOC(), "Input Image Traits: ", image.format().to_string() );
    // Convert to Image_Memory
    Image_Memory<typename Compound_Channel_Cast<typename ImageType::pixel_type,uint8_t>::type> temp;
    temp = image;
    return view_image( window_name, temp );
}

} // End of tmns::image::utility namespace