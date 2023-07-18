/**
 * @file    View_Utilities.hpp
 * @author  Marvin Smith
 * @date    7/10/2023
*/
#pragma once

// Terminus Image Libraries
#include "../error/ErrorCategory.hpp"
#include "../Image_Base.hpp"

// OpenCV Libraries
#include <opencv2/highgui.hpp>

namespace tmns::image::utility {

template <typename ImageType>
ImageResult<void> view_image( const std::string&      window_name,
                              const Image<ImageType>& image )
{
    // convert to opencv image
    cv::Mat tmp_image( image.rows(), image.cols(), CV_MAKE_TYPE(CV_8U, image.channels()), image.data() );

    cv::imshow( window_name.c_str(), tmp_image );
    cv::waitKey( 0 );
    return tmns::outcome::ok();
}

} // End of tmns::warp::utility namespace