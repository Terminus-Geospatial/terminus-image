/**
 * @file    TEST_read_image_disk.cpp
 * @author  Marvin Smith
 * @date    7/28/2023
 */
#include <gtest/gtest.h>

// Terminus Libraries
#include <terminus/log/utility.hpp>
#include <terminus/image/io/read_image_disk.hpp>
#include <terminus/image/pixel/Channel_Types.hpp>
#include <terminus/image/pixel/Pixel_RGB.hpp>
#include <terminus/image/types/Image_Memory.hpp>
#include <terminus/image/utility/View_Utilities.hpp>

/********************************************/
/*          Read and write imagery          */
/********************************************/
TEST( read_image_disk, read_simple_test )
{
    namespace wc = tmns::image;

    // Load an image
    std::filesystem::path image_to_load { "./data/images/jpeg/lena.jpg" };
    tmns::log::trace( ADD_CURRENT_LOC(), "Loading Image" );
    auto result = wc::io::read_image_disk<wc::PixelRGB_u8>( image_to_load );
    tmns::log::trace( ADD_CURRENT_LOC(), "End of read_image_disk" );

    if( result.has_error() )
    {
        tmns::log::error( ADD_CURRENT_LOC(), "error reading image: ", result.error().message() );
    }
    ASSERT_FALSE( result.has_error() );
    auto image = result.assume_value();

    ASSERT_FALSE( result.has_error() );

    // View the image
    if( false )
    {
        auto res = wc::utility::view_image( "Dummy Window", image );
    }

    ASSERT_EQ( image.cols(), 512 );
    ASSERT_EQ( image.rows(), 512 );
    ASSERT_EQ( image.channels(), 3 );
    ASSERT_EQ( image.format().channel_type(), wc::Channel_Type_Enum::UINT8 );
    ASSERT_EQ( image.format().pixel_type(),   wc::Pixel_Format_Enum::RGB );

}