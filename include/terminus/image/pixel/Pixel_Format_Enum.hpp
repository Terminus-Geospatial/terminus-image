/**
 * @file    Pixel_Format_Enum.hpp
 * @author  Marvin Smith
 * @date    7/13/2023
*/
#pragma once

// Terminus Libraries
#include <terminus/core/error/ErrorCategory.hpp>

namespace tmns::image {

/**
 * Structure representing pixel type enumerations and names
*/
enum class Pixel_Format_Enum
{
    UNKNOWN = 0,
    SCALAR  = 1,
    GRAY    = 2,
    GRAYA   = 3,
    RGB     = 4,
    RGBA    = 5
}; // End of Pixel_Format_Enum enumeration

/**
 * Convert enumeration to string
*/
std::string enum_to_string( Pixel_Format_Enum val );

/**
 * Get the number of channels for the given pixel format enumeration.
*/
ImageResult<int> num_channels( Pixel_Format_Enum value );

} // End of tmns::image namespace