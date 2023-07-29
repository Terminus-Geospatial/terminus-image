/**
 * @file    TEST_Fundamental_Types.cpp
 * @author  Marvin Smith
 * @date    7/23/2023
*/
#include <gtest/gtest.h>

// Terminus Libraries
#include <terminus/image/pixel/Pixel_RGBA.hpp>
#include <terminus/image/types/Fundamental_Types.hpp>

/******************************************/
/*      Test the Is-Scalar Type-Trait     */
/******************************************/
TEST( Fundamental_Types, Is_Scalar )
{
    ASSERT_TRUE( tmns::image::Is_Scalar<float>::value );
    ASSERT_TRUE( tmns::image::Is_Scalar<uint8_t>::value );

    ASSERT_FALSE( tmns::image::Is_Scalar<tmns::image::PixelRGBA_u8>::value );
}
