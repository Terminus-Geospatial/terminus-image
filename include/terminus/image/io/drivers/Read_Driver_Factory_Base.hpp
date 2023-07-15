/**
 * @file    Read_Driver_Factory_Base.hpp
 * @author  Marvin Smith
 * @date    7/14/2023
*/
#pragma once

// C++ Libraries
#include <filesystem>
#include <memory>

// Terminus Libraries
#include "../../error/ErrorCategory.hpp"
#include "../../Image_Resource_Base.hpp"

namespace tmns::image::io{

/**
 * @class Read_Driver_Factory_Base
 *
 * Simple class to help construct Read/Write image resources
*/
class Read_Driver_Factory_Base
{
    public:

        /// Disk Driver Pointer Type
        typedef Read_Image_Resource_Base::ptr_t DriverT;

        /// Pointer Type
        typedef std::shared_ptr<Read_Driver_Factory_Base> ptr_t;

        /// Destructor
        virtual ~Read_Driver_Factory_Base() = default;

        /**
         * Check if the file type is supported for this driver
        */
        virtual bool is_image_supported( const std::filesystem::path& pathname ) const = 0;

        /**
         * Build a new Read-Image-Resource object.
        */
        virtual ImageResult<DriverT> create( const std::filesystem::path& pathname ) const = 0;

}; // end of Read_Driver_Factory_Base class

} // End of tmns::image::io namespace