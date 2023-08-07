/**
 * @file    TEST_find_keypoints.cpp
 * @author  Marvin Smith
 * @date    7/20/2023
*/
#include <gtest/gtest.h>

// C++ Libraries
#include <filesystem>

// Terminus Libraries
#include <terminus/image/io/read_image_disk.hpp>
#include <terminus/image/pixel/Pixel_RGBA.hpp>
//#include <terminus/feature/find_keypoints.hpp>

namespace tx=tmns::image;

/************************************************************/
/*          Test the Find Keypoints on a test image         */
/*          - Disk Image Example                            */
/************************************************************/
TEST( find_feature_points, disk_image_example_01 )
{
    // Using a NITF, load the image, then perform feature detection on it
    std::filesystem::path image_to_load( "data/tif/test_image_01.tif" );

    auto view = tx::io::read_image_disk<tx::PixelRGBA_f64>( image_to_load );
    ASSERT_FALSE( view.has_error() );

    auto disk_image = view.assume_value();

    // Create the feature detector
    

}