/**
 * @file    Channel_Type_Enum.hpp
 * @author  Marvin Smith
 * @date    7/13/2023
*/
#pragma once

// Terminus Libraries
#include "../error/ErrorCategory.hpp"

namespace tmns::image {

enum Channel_Type_Enum
{
    UNKNOWN = 0 /**< Error condition.*/,
    UINT8   = 1,
    UINT12  = 2,
    UINT14  = 3,
    UINT16  = 4,
}; // end of Channel_Type_Enum enumeration

/**
 * Function to get the size of the channel in bytes.
 * Throws an error if value is unknown.
*/
ImageResult<size_t> channel_size_bytes( Channel_Type_Enum val );

} // end of tmns::image namespace