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

template <typename ImageType>
ImageResult<void> view_image( const std::string&             window_name,
                              const Image_Memory<ImageType>& image )
{
    // convert to opencv image
    cv::Mat tmp_image( image.rows(), image.cols(), CV_MAKE_TYPE(CV_8U, image.channels()), image.data() );

    cv::imshow( window_name.c_str(), tmp_image );
    cv::waitKey( 0 );
    return tmns::outcome::ok();
}

} // End of tmns::image::utility namespace