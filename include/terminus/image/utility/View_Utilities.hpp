/**
 * @file    View_Utilities.hpp
 * @author  Marvin Smith
 * @date    7/10/2023
*/
#pragma once

// Terminus Image Libraries
#include "../types/Image_Base.hpp"

// Terminus Libraries
#include <terminus/core/error/ErrorCategory.hpp>

// OpenCV Libraries
#include <opencv2/highgui.hpp>

namespace tmns::image::utility {

/**
 * Simple test tool for viewing an image
*/
template <typename ImageType>
ImageResult<void> view_image( const std::string&             window_name,
                              const Image_Memory<ImageType>& image )
{
    // convert to opencv image
    tmns::log::trace( "Creating OpenCV Image" );
    cv::Mat tmp_image( image.rows(), image.cols(), CV_MAKE_TYPE(CV_8U, image.channels()), image.data() );

    tmns::log::trace( "Rendering window: ", window_name );
    cv::imshow( window_name.c_str(), tmp_image );
    cv::waitKey( 0 );
    return tmns::outcome::ok();
}

/**
 * View any image
*/
template <typename ImageType>
ImageResult<void> view_image( const std::string&  window_name,
                              const ImageType&    image )
{
    // Convert to Image_Memory
    Image_Memory<typename ImageType::pixel_type> temp;
    temp = image;
    return view_image( window_name, temp );
}

} // End of tmns::image::utility namespace