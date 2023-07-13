/**
 * @file    TEST_ImageIO.cpp
 * @author  Marvin Smith
 * @date    7/7/2023
 */
#include <gtest/gtest.h>

// Terminus Libraries
#include <terminus/log/utility.hpp>
#include <terminus/warpcore/image/Image_Memory.hpp>
#include <terminus/warpcore/io/Image_IO.hpp>

/********************************************/
/*          Read and write imagery          */
/********************************************/
TEST( io_ImageIO, read_image_memory )
{
    namespace wc = tmns::warp;

    // Load an image
    std::filesystem::path image_to_load { "./data/sample_images/jpeg/lena.jpg" };
    wc::image::Image<wc::image::PixelRGB_u8> image;
    auto result = wc::io::Read_Image( image_to_load,
                                      image );

    ASSERT_FALSE( result.has_error() );

    // View the image
    if( true )
    {
        wc::utils::View_Image( "Dummy Window", image );
    }

    FAIL();
}