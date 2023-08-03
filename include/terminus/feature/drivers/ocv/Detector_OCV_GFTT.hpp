/**
 * @file    Detector_OCV_GFFT.hpp
 * @author  Marvin Smith
 * @date    7/30/2023
*/
#pragma once

// Terminus Feature Libraries
#include "config/Detector_Config_OCV_GFTT.hpp"
#include "Detector_OCV_Base.hpp"

namespace tmns::feature::ocv {

/**
 * OpenCV implementation of the Shi-Thomasi Good-Features-To-Track
 * algorithm.
*/
class Detector_OCV_GFFT : public Detector_OCV_Base
{
    public:

        Detector_OCV_GFFT( Detector_Config_OCV_GFTT::ptr_t config );

    private:

        /// Configuration
        Detector_Config_OCV_GFTT::ptr_t m_config { nullptr };

}; // End of Detector_OCV_GFFT class

} // End of tmns::feature::ocv namespace