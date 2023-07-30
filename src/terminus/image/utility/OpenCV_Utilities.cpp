/**
 * @file    OpenCV_Utilities.cpp
 * @author  Marvin Smith
 * @date    7/29/2023
*/
#include "OpenCV_Utilities.hpp"

// OpenCV Libraries
#include <opencv4/opencv2/core.hpp>

// Terminus Libraries
#include <terminus/outcome/Result.hpp>

namespace tmns::image::utility::ocv {

/****************************************/
/*      Get an OpenCV Data Type Code    */
/****************************************/
ImageResult<int> get_data_type_code( Channel_Type_Enum  channel_type )
{
    switch( channel_type )
    {
        case Channel_Type_Enum::UINT8:
            return outcome::ok<int>( CV_8U );

        case Channel_Type_Enum::UINT12:
        case Channel_Type_Enum::UINT14:
        case Channel_Type_Enum::UINT16:
            return outcome::ok<int>( CV_16U );

        case Channel_Type_Enum::INT16:
            return outcome::ok<int>( CV_16S );

        case Channel_Type_Enum::UINT32:
            return outcome::ok<int>( CV_32S );

        case Channel_Type_Enum::FLOAT32:
            return outcome::ok<int>( CV_32F );

        case Channel_Type_Enum::FLOAT64:
            return outcome::ok<int>( CV_64F );

        case Channel_Type_Enum::UINT64:
        case Channel_Type_Enum::UNKNOWN:
        default:
            return outcome::fail( core::error::ErrorCode::INVALID_CHANNEL_TYPE,
                                  "Unsupported Channel-Type" );
    }
}

/****************************************/
/*      Get an OpenCV Pixel Type Code   */
/****************************************/
ImageResult<int> get_pixel_type_code( Pixel_Format_Enum  pixel_type,
                                      Channel_Type_Enum  channel_type )
{
    // Get the channel count
    auto ch_res = num_channels( pixel_type );
    if( ch_res.has_error() )
    {
        return outcome::fail( core::error::ErrorCode::INVALID_PIXEL_TYPE,
                              "Unable to create OpenCV pixel type. Pixel-Type: ",
                              enum_to_string( pixel_type ), ", error msg: ",
                             ch_res.error().message() );
    }

    // Get the pixel type
    auto pt_res = get_data_type_code( channel_type );
    if( pt_res.has_error() )
    {
        return outcome::fail( core::error::ErrorCode::INVALID_CHANNEL_TYPE,
                              "Unable to create OpenCV channel type. ",
                              pt_res.error().message() );
    }

    return outcome::ok<int>( CV_MAKE_TYPE( pt_res.value(),
                                           ch_res.value() ) );
}

} // End of tmns::image::utility::ocv namespace