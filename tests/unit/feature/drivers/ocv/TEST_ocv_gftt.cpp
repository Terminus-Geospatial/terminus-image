/**
 * @file    TEST_ocv_gftt.cpp
 * @author  Marvin Smith
 * @date    7/30/2023
*/
#include <gtest/gtest.h>

// Terminus Libraries
#include <terminus/image/io/read_image_disk.hpp>
#include <terminus/image/utility/View_Utilities.hpp>

// OpenCV Libraries
#include <opencv2/features2d.hpp>
#include <opencv2/highgui.hpp>

//namespace tf = tmns::feature;
namespace tx = tmns::image;

TEST( ft_drv_ocv_good_features_to_track, functional_test )
{
    // Can Shi-Thomasi work on the various pixel types?
    std::filesystem::path image_to_load { "./data/images/jpeg/lena.jpg" };

    // Load image in different formats
    tx::Image_Memory<tx::PixelGray_u8>  img_u8  = tx::io::read_image_disk<tx::PixelGray_u8>(  image_to_load ).value();
    tx::Image_Memory<tx::PixelGray_u16> img_u16 = tx::io::read_image_disk<tx::PixelGray_u16>( image_to_load ).value();
    tx::Image_Memory<tx::PixelGray_f32> img_f32 = tx::io::read_image_disk<tx::PixelGray_f32>(    image_to_load ).value();
    tx::Image_Memory<tx::PixelGray_f64> img_f64 = tx::io::read_image_disk<tx::PixelGray_f64>(   image_to_load ).value();

    // Create an OpenCV GFTT detector
    auto detector = cv::GFTTDetector::create();

    // UInt8 Test
    cv::Mat mat_u8( img_u8.buffer().cols(),
                    img_u8.buffer().rows(),
                    CV_8UC1,
                    img_u8.buffer().data() );
    std::vector<cv::KeyPoint> kp_u8;

    ASSERT_NO_THROW( { detector->detect( mat_u8, kp_u8 ); } );
    ASSERT_TRUE( kp_u8.size() >  10 );

    tx::utility::view_image( "Window", img_u16 );

    // UInt16 Test
    cv::Mat mat_u16( img_u16.buffer().cols(),
                     img_u16.buffer().rows(),
                     CV_16UC1,
                     img_u16.buffer().data() );

    cv::imshow( "win", mat_u16 );
    cv::waitKey(0);
    std::vector<cv::KeyPoint> kp_u16;

    ASSERT_ANY_THROW( { detector->detect( mat_u16, kp_u16 ); } );
    ASSERT_TRUE( kp_u16.empty() );

    // Float 32 Test
    cv::Mat mat_f32( img_f32.buffer().cols(),
                     img_f32.buffer().rows(),
                     CV_32FC1,
                     img_f32.buffer().data() );
    std::vector<cv::KeyPoint> kp_f32;

    ASSERT_NO_THROW( { detector->detect( mat_f32, kp_f32 ); } );
    ASSERT_TRUE( kp_f32.size() >  10 );

    // Float 64 Test
    cv::Mat mat_f64( img_f64.buffer().cols(),
                     img_f64.buffer().rows(),
                     CV_64FC1,
                     img_f64.buffer().data() );
    std::vector<cv::KeyPoint> kp_f64;

    ASSERT_NO_THROW( { detector->detect( mat_f64, kp_f64 ); } );
    ASSERT_TRUE( kp_f64.size() >  10 );


    cv::imshow( "win", mat_u8 );
    cv::waitKey(0);
}