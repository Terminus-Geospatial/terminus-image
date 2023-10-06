/**
 * @file    TEST_convert.cpp
 * @author  Marvin Smith
 * @date    10/6/2023
*/
#include <gtest/gtest.h>

// Terminus Libraries
#include <terminus/image/pixel/convert.hpp>
#include <terminus/log/utility.hpp>

// C++ Libraries
#include <array>

/************************************/
/*      Convert Int to Float        */
/************************************/
TEST( image_convert, channel_convert_int_to_float )
{
    std::array<int8_t,4> int08_arr { 0, 50, 100, 127 };
    std::array<float,4>  flt32_arr { 0, 0, 0, 0 };

    std::array<float,4>  flt32_exp { 0, 0, 0, 0 };   

    // Apply the operation.
    for( size_t i = 0; i < int08_arr.size(); i++ )
    {
        tmns::log::trace( "Iteration: ", i );
        tmns::image::channel_convert_int_to_float( &int08_arr[i],
                                                   &flt32_arr[i] );
        
        ASSERT_NEAR( flt32_arr[i], flt32_exp[i], 0.001 );
    }

}