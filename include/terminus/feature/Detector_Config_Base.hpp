/**
 * @file    Detector_Config_Base.hpp
 * @author  Marvin Smith
 * @date    7/30/2023
*/
#pragma once

// C++ Libraries
#include <string>

namespace tmns::feature {

class Detector_Config_Base
{
    public:

        /// Pointer Type
        typedef std::shared_ptr<Detector_Config_Base> ptr_t;

        Detector_Config_Base() = default;

        /**
         * Get the name to use for the detector's logger instance
        */
        virtual std::string logger_name() const = 0;

        /**
         * Print log-friendly string
         */
        virtual std::string to_string( size_t offset ) const = 0;

}; // End of Detector_Config_Base class

} // End of tmns::feature namespace