/**
 * @file    TEST_ImageIO.cpp
 * @author  Marvin Smith
 * @date    7/7/2023
 */
#include <gtest/gtest.h>

// Terminus Libraries
#include <terminus/log/utility.hpp>
#include <terminus/image/io/read_image.hpp>
#include <terminus/image/pixel/Channel_Types.hpp>
#include <terminus/image/pixel/Pixel_RGB.hpp>
#include <terminus/image/utility/View_Utilities.hpp>
#include <terminus/image/Image_Memory.hpp>

/********************************************/
/*          Read and write imagery          */
/********************************************/
TEST( io_read_image, read_image_memory )
{
    namespace wc = tmns::image;

    // Load an image
    std::filesystem::path image_to_load { "./data/sample_images/jpeg/lena.jpg" };
    auto result = wc::io::read_image<wc::Image<wc::PixelRGB_u8>>( image_to_load );

    auto image = result.assume_value();

    ASSERT_FALSE( result.has_error() );

    // View the image
    if( true )
    {
        auto res = wc::utility::view_image( "Dummy Window", image );
    }

    FAIL();
}