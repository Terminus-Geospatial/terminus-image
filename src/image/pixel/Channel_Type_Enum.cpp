/**
 * @file    Channel_Type_Enum.cpp
 * @author  Marvin Smith
 * @file    7/13/2023
*/
#include "Channel_Type_Enum.hpp"

// Terminus Libraries
#include "../error/ErrorCategory.hpp"

// External Terminus Libraries
#include <terminus/outcome/Result.hpp>

namespace tmns::image {

/********************************************************/
/*          Get the size of the channel in bytes        */
/********************************************************/
ImageResult<size_t> channel_size_bytes( Channel_Type_Enum val )
{
    switch( val )
    {
        // Single-Byte Entries
        case Channel_Type_Enum::UINT8:
            return outcome::ok<size_t>( 1 );

        // Error Conditions
        case Channel_Type_Enum::UNKNOWN:
        default:
            return outcome::fail( error::ErrorCode::INVALID_CHANNEL_TYPE );
    }
}

} // end of tmns::image namespace