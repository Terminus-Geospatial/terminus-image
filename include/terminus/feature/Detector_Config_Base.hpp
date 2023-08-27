/**
 * @file    Detector_Config_Base.hpp
 * @author  Marvin Smith
 * @date    7/30/2023
*/
#pragma once

// C++ Libraries
#include <string>

// Terminus Libraries
#include <terminus/math/Size.hpp>

namespace tmns::feature {

class Detector_Config_Base
{
    public:

        /// Pointer Type
        typedef std::shared_ptr<Detector_Config_Base> ptr_t;

        Detector_Config_Base() = default;

        /**
         * Check if we must enforce a specific tile size.
         * 
         * If true, the detector will ignore the specified tile size.
         * If false, the detector will chop the image into tiles, then process
         * each individually on a thread pool.
         */
        virtual bool allow_custom_tile_size() const = 0;

        /**
         * Get the tile size in pixels
         */
        virtual math::Size2i tile_size_pixels() const = 0;

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