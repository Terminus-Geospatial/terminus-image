/**
 * @file    Detector_Generator_Base.hpp
 * @author  Marvin Smith
 * @date    8/27/2023
*/
#pragma once

// C++ Libraries
#include <memory>

// Terminus Feature Libraries
#include "Detector_Base.hpp"

// Terminus Libraries
#include <terminus/core/error/ErrorCategory.hpp>

namespace tmns::feature {

class Detector_Generator_Base
{
    public:

        typedef std::shared_ptr<Detector_Generator_Base> ptr_t;

        virtual ImageResult<Detector_Base::ptr_t> generate( Detector_Config_Base::ptr_t config ) = 0;

}; // End of Detector_Generator_Base class

} // End of tmns::feature namespace