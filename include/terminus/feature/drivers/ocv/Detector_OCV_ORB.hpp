/**
 * @file    Detector_OCV_ORB.hpp
 * @author  Marvin Smith
 * @date    8/27/2023
*/
#pragma once

// Terminus Feature Libraries
#include "../../Detector_Generator_Base.hpp"
#include "config/Detector_Config_OCV_ORB.hpp"
#include "Detector_OCV_Base.hpp"

namespace tmns::feature::ocv {

/**
 * OpenCV implementation of the Oriented Brief Keypoint Detector
 * algorithm.
*/
class Detector_OCV_ORB : public Detector_OCV_Base
{
    public:

        /**
         * Default Constructor
         */
        Detector_OCV_ORB();

        /**
         * Parameterized Constructor
        */
        Detector_OCV_ORB( Detector_Config_Base::ptr_t config );

        /**
         * Destructor
        */
        ~Detector_OCV_ORB() override = default;

        /**
         * Process the image and detect keypoints
         * 
         * @param image Image to run detection on
         * @param cast_if_ctype_unsupported Cast to baseline channel type if input is not supported.
         */
        ImageResult<Interest_Point_List> process_image( const image::Image_Buffer& image,
                                                        bool                        cast_if_ctype_unsupported ) override;

        /**
         * Get the class name
         */
        std::string class_name() const override;

    private:

        /// Configuration
        Detector_Config_OCV_ORB::ptr_t m_config { nullptr };

}; // End of Detector_OCV_ORB class


class Detector_Generator_OCV_ORB : public Detector_Generator_Base
{
    public:

        /**
         * Build a new instance of the feature detector
        */
        ImageResult<Detector_Base::ptr_t> generate( Detector_Config_Base::ptr_t config ) override;

}; // End of Detector_Generator_OCV_ORB

} // End of tmns::feature::ocv namespace