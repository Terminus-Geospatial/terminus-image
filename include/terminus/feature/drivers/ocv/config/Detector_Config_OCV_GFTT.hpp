/**
 * @file    Detector_Config_OCV_GFTT.hpp
 * @author  Marvin Smith
 * @date    7/30/2023
*/
#pragma once

// Terminus Feature Libraries
#include "Detector_Config_OCV_Base.hpp"

namespace tmns::feature::ocv {

/**
 * Configuration options for the Shi-Thomasi GFTT Library
*/
class Detector_Config_OCV_GFTT : public Detector_Config_OCV_Base
{
    public:

        /**
         * OpenCV Shi-Thomasi Good-Features-To-Track configuration.
         *
         * These parameters are lifted from the OpenCV documentation.
         * @see https://docs.opencv.org/4.x/df/d21/classcv_1_1GFTTDetector.html
        */
        Detector_Config_OCV_GFTT( int    max_corners         = 1000,
                                  double quality_level       = 0.01,
                                  double min_distance        = 1,
                                  int    block_size          = 3,
                                  bool   use_harris_detector = false,
                                  double k                   = 0.04 );

        /**
         * Get the max corners.
         */
        double max_corners() const;

        /**
         * Get the quality level
         */
        double quality_level() const;

        /**
         * Min distance
         */
        double min_distance() const;

        /**
         * Block Size
         */
        int block_size() const;

        /**
         * Use Harris Detector
         */
        bool use_harris_detector() const;

        /**
         * Harris Free Parameters
         */
        double k() const;

        /**
         * Get the name to use for the detector's logger instance
        */
        std::string logger_name() const override;

    private:

        /// Max corners to create
        int m_max_corners { 1000 };

        /// Quality metric
        double m_quality_level { 0.01 };

        /// Minimum Distance Between Points
        double m_min_distance { 1 };

        /// Block Size
        int m_block_size { 3 };

        /// Use Harris Detector
        bool m_use_harris_detector { false };

        /// Harris Detector Free Parameter
        double m_k { 0.04 };

}; // End of Detector_Config_OCV_GFTT class

} // End of tmns::feature::ocv namespace