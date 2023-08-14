/**
 * @file    TEST_drawing_functions.cpp
 * @author  Marvin Smith
 * @date    8/13/2023
*/
#include <gtest/gtest.h>

// Terminus Libraries
#include <terminus/image/io/read_image_disk.hpp>
#include <terminus/image/pixel/Pixel_RGB.hpp>
#include <terminus/image/operations/drawing/drawing_functions.hpp>
#include <terminus/image/utility/View_Utilities.hpp>

namespace tx = tmns::image;

/************************************************/
/*          Test the Draw Line Function         */
/************************************************/
TEST( drawing_functions, draw_line )
{
    // Image to process
    std::filesystem::path image_to_load { "./data/images/jpeg/lena.jpg" };
    ASSERT_TRUE( std::filesystem::exists( image_to_load ) );
    
    // Read Image
    typedef tx::PixelRGB_u8 PixelT;
    tx::Image_Memory<PixelT> img_rgb_u8 = tx::io::read_image_disk<PixelT>( image_to_load ).value();

    // Draw the line
    auto result = tx::ops::draw_line( img_rgb_u8,
                                      tmns::math::Point2i( { 50, 50 } ),
                                      tmns::math::Point2i( { 400, 400 } ),
                                      PixelT( 0, 255, 0 ),
                                      30 );

    // Visualize
    tx::utility::view_image( "Rendered Image", result );
}