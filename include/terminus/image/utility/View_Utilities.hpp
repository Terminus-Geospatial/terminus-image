/**
 * @file    View_Utilities.hpp
 * @author  Marvin Smith
 * @date    7/10/2023
*/
#pragma once

// Terminus Image Libraries
#include "../error/ErrorCategory.hpp"
#include "../Image_Base.hpp"

namespace tmns::image::utility {

template <typename ImageType>
ImageResult<void> view_image( const std::string&           window_name,
                              const Image_Base<ImageType>& image )
{
    // convert to opencv image

    return tmns::outcome::ok();
}

} // End of tmns::warp::utility namespace