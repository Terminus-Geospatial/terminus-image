/**
 * @file    Write_Driver_Factory_Base.hpp
 * @author  Marvin Smith
 * @date    7/14/2023
*/
#pragma once

// C++ Libraries
#include <memory>

// Terminus Libraries
#include "../../types/Image_Resource_Base.hpp"

namespace tmns::image::io{

/**
 * @class Write_Driver_Factory_Base
 *
 * Simple class to help construct Write/Write image resources
*/
class Write_Driver_Factory_Base
{
    public:

        typedef std::shared_ptr<Write_Driver_Factory_Base> ptr_t;

        /**
         * Build a new Write-Image-Resource object.
        */
        virtual Write_Image_Resource_Base::ptr_t create() const = 0;

}; // end of Write_Driver_Factory_Base class

} // End of tmns::image::io namespace