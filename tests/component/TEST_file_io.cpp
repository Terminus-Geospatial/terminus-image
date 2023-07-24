/**
 * @file    TEST_file_io.cpp
 * @author  Marvin Smith
 * @date    7/22/2023
*/

// C++ Libraries
#include <filesystem>

// Terminus Libraries
#include <terminus/log/configure.hpp>
#include <terminus/image/io/read_image.hpp>
#include <terminus/image/io/write_image.hpp>

namespace timg = tmns::image;

int main( int argc, char* [] )
{
    // Parse Command-Line Options
    std::filesystem::path input_image( argv[1] );
    std::filesystem::path output_image( argv[2] );

    // Load the image
    auto image_res = timg::io::read_image_disk<timg::PixelRGBA_f64>( input_image );

    // Write the image
    auto write_status = timg::io::write_image( image_res.value() );
}