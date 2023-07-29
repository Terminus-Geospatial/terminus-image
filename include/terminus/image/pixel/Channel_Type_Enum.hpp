/**
 * @file    Channel_Type_Enum.hpp
 * @author  Marvin Smith
 * @date    7/13/2023
*/
#pragma once

// Terminus Libraries
#include <terminus/core/error/ErrorCategory.hpp>

namespace tmns::image {

enum Channel_Type_Enum
{
    UNKNOWN     =  0 /**< Error condition.*/,
    UINT8       =  1,
    UINT12      =  2,
    UINT14      =  3,
    UINT16      =  4,
    UINT32      =  5,
    UINT64      =  6,
    INT16       =  7,
    INT32       =  8,
    INT64       =  9,
    FLOAT32     = 10,
    FLOAT64     = 11,
    FLOAT32Free = 12,
    FLOAT64Free = 13,
}; // end of Channel_Type_Enum enumeration

/**
 * Convert Channel_Type_Enum to a string
*/
std::string enum_to_string( Channel_Type_Enum val );

/**
 * Return true if enumeration is "integer" type (aka not float)
*/
bool is_integer_type( Channel_Type_Enum value );

/**
 * Function to get the size of the channel in bytes.
 * Throws an error if value is unknown.
*/
ImageResult<size_t> channel_size_bytes( Channel_Type_Enum val );

} // end of tmns::image namespace