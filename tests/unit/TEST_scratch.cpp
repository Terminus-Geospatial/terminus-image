/**
 * @file    TEST_scratch.cpp
 * @author  Marvin Smith
 * @date    8/11/2023
*/
#include <gtest/gtest.h>

// Terminus Libraries
#include <terminus/log/utility.hpp>
#include <terminus/image/io/read_image_disk.hpp>
#include <terminus/image/pixel/Pixel_RGB.hpp>
#include <terminus/image/types/Image_Memory.hpp>
#include <terminus/image/utility/View_Utilities.hpp>
#include <terminus/math/Point.hpp>
#include <terminus/math/Size.hpp>

// C++ Libraries
#include <algorithm>
#include <atomic>
#include <cassert>


namespace tx = tmns::image;



TEST( scratch, draw_line_demo )
{
    // Image to process
    std::filesystem::path image_to_load { "./data/images/jpeg/lena.jpg" };
    ASSERT_TRUE( std::filesystem::exists( image_to_load ) );
    
    // Read Image
    typedef tx::PixelRGB_u8 PixelT;
    tx::Image_Memory<PixelT> img_rgb_u8 = tx::io::read_image_disk<PixelT>( image_to_load ).value();

    
}
