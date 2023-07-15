/**
 * @file    Read_Image_Resource_Memory_OpenCV.hpp
 * @author  Marvin Smith
 * @date    7/14/2023
*/
#pragma once

// C++ Libraries
#include <memory>

// Terminus Libraries
#include "../../Read_Image_Resource_Memory.hpp"

namespace tmns::image::io::ocv {

/**
 * OpenCV driver for loading images into memory
*/
class Read_Image_Resource_Memory_OpenCV : public Read_Image_Resource_Memory
{
    public:

        /**
         * Check if the pathname provided points to a dataset the driver supports.
        */
        bool image_is_supported( const std::filesystem::path& pathname ) const override;

        /**
         * Create a new resource for the supported driver
        */
        ImageResult<Read_Image_Resource_Memory::ptr_t> create() const override;

        /**
         * Create a new resource and open the image
        */
        ImageResult<Read_Image_Resource_Memory::ptr_t> create_and_open( const std::filesystem::path& pathname ) const override;

        Image_Format format() const override;
}; // end of Read_Image_Resource_Memory_OpenCV Class

} // end of tmns::image::io::ocv namespace