/**
 * @file    OpenCV_Utilities.hpp
 * @author  Marvin Smith
 * @date    7/29/2023
*/
#pragma once

// Terminus Image Libraries
#include "../pixel/Channel_Type_Enum.hpp"
#include "../pixel/Pixel_Format_Enum.hpp"

// Terminus Libraries
#include <terminus/core/error/ErrorCategory.hpp>


namespace tmns::image::utility::ocv {

/**
 * Given the channel type, generate an OpenCV channel code (ex: CV_8U)
*/
ImageResult<int> get_data_type_code( Channel_Type_Enum channel_type );

/**
 * Given an pixel-type and channel-type, generate the pixel type
 * code required to create an OpenCV Mat.
*/
ImageResult<int> get_pixel_type_code( Pixel_Format_Enum  pixel_type,
                                      Channel_Type_Enum  channel_type );

} // End of tmns::image::utility::ocv