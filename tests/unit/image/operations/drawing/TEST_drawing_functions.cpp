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
    tmns::math::Point2i center( { (int)img_rgb_u8.cols() / 2,
                                  (int)img_rgb_u8.rows() / 2 } );

    double radius = std::min( img_rgb_u8.cols() / 3.0,
                              img_rgb_u8.rows() / 3.0 );
    
    tx::Image_Memory<PixelT> result = img_rgb_u8;
    for( int i = 0; i < 6; i++ )
    {
        double angle = 360.0 * i / 6;

        auto p1 = center;
        auto p2 = center;

        p1.x() -= std::round( std::cos( angle ) * radius );
        p1.y() -= std::round( std::sin( angle ) * radius );
        
        p2.x() += std::round( std::cos( angle ) * radius );
        p2.y() += std::round( std::sin( angle ) * radius );

        result = tx::ops::draw_line( result,
                                     p1,
                                     p2,
                                     PixelT( rand() % 255,
                                             rand() % 255,
                                             rand() % 255 ),
                                     10 );
    }

    // Visualize
    tx::utility::view_image( "Rendered Image", result );
}

/********************************************/
/*      Test the Draw Circle Function       */
/********************************************/
TEST( drawing_functions, draw_circle )
{
    // Image to process
    std::filesystem::path image_to_load { "./data/images/jpeg/lena.jpg" };
    ASSERT_TRUE( std::filesystem::exists( image_to_load ) );
    
    // Read Image
    typedef tx::PixelRGB_u8 PixelT;
    tx::Image_Memory<PixelT> img_rgb_u8 = tx::io::read_image_disk<PixelT>( image_to_load ).value();

    // Draw the line
    auto result = tx::ops::draw_circle( img_rgb_u8,
                                        tmns::math::Point2i( { 200, 200 } ),
                                        100.0,
                                        PixelT( 0, 255, 0 ),
                                        1 );

    // Visualize
    tx::utility::view_image( "Rendered Image", result );
}

/***********************************************/
/*      Test the Draw Rectangle Function       */
/***********************************************/
TEST( drawing_functions, draw_rectangle )
{
    // Image to process
    std::filesystem::path image_to_load { "./data/images/jpeg/lena.jpg" };
    ASSERT_TRUE( std::filesystem::exists( image_to_load ) );
    
    // Read Image
    typedef tx::PixelRGB_u8 PixelT;
    tx::Image_Memory<PixelT> img_rgb_u8 = tx::io::read_image_disk<PixelT>( image_to_load ).value();

    // Draw the line
    auto result = tx::ops::draw_rectangle( img_rgb_u8,
                                           tmns::math::Rect2i( tmns::math::Point2i( { 100, 100 } ),
                                                               tmns::math::Point2i( { 300, 300 } ) ),
                                           PixelT( 0, 255, 0 ),
                                           10 );

    // Visualize
    tx::utility::view_image( "Rendered Image", result );
}