/**
 * @file    TEST_Collection_Resource_File.cpp
 * @author  Marvin Smith
 * @date    8/26/2023
*/
#include <gtest/gtest.h>

// Terminus Libraries
#include <terminus/image/collection/Collection_Resource_File.hpp>

// C++ Libraries
#include <filesystem>

namespace tx = tmns::image;

/**********************************************/
/*          Collection Resource File          */
/**********************************************/
TEST( cx_Collection_Resource_File, functional_test )
{
    // Collection path to load
    std::filesystem::path collection_path { "./data/collection/dummy-collection.toml" };

    auto resource = tx::cx::Collection_Resource_File<tx::PixelGray_f32>::load_image_list( collection_path );

    // Verify the resource is properly constructed
    if( resource.has_error() )
    {
        tmns::log::error( "About to fail: ", resource.error().message() );
    }
    ASSERT_FALSE( resource.has_error() );

    // Check the image list
    ASSERT_EQ( resource.value()->size(), 2 );
}