/**
 * @file    Pixel_Format_Enum.cpp
 * @author  Marvin Smith
 * @date    7/14/2023
*/
#include "Pixel_Format_Enum.hpp"

// Terminus Libraries
#include <terminus/outcome/macros.hpp>

namespace tmns::image {

/****************************************************************/
/*          Get the number of channels for the PixelType        */
/****************************************************************/
ImageResult<int> num_channels( Pixel_Format_Enum value )
{
    switch( value )
    {
        case Pixel_Format_Enum::GRAY:
        case Pixel_Format_Enum::SCALAR:
            return outcome::ok<int>( 1 );

        case Pixel_Format_Enum::GRAYA:
            return outcome::ok<int>( 2 );

        case Pixel_Format_Enum::RGB:
            return outcome::ok<int>( 3 );

        case Pixel_Format_Enum::RGBA:
            return outcome::ok<int>( 3 );

        case Pixel_Format_Enum::UNKNOWN:
        default:
            return outcome::fail( error::ErrorCode::INVALID_PIXEL_TYPE );
    }
}

} // end of tmns::image namespace