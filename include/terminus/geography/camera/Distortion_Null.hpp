/**
 * @file    Distortion_Null.hpp
 * @author  Marvin Smith
 * @date    11/10/2023
*/
#pragma once

// Terminus Libraries
#include <terminus/geography/camera/Distortion_Base.hpp>

namespace tmns::geo::cam {

/**
 * Lens distortion model that is mostly just a pass-through
 */
class Distortion_Null : public Distortion_Base
{
    public:

        /**
         * Destructor
         */
        ~Distortion_Null() override = default;

        /**
         * Convert from Undistorted to Distorted
         */
        math::Point2d to_distorted( const std::shared_ptr<Camera_Model_Pinhole> camera_model,
                                    const math::Point2d&                        pixel_coord ) const override;

        /**
         * Convert from Distorted to Undistorted
         */
        math::Point2d to_undistorted( const std::shared_ptr<Camera_Model_Pinhole> camera_model,
                                      const math::Point2d&                        pixel_coord ) const override;

        /**
         * Check if method has fast distortion (true)
         */
        bool has_fast_distort() const override;

        /**
         * Check if method has fast undistortion (true)
         */
        bool has_fast_undistort() const override;

        /**
         * Return a vector containing all the distortion parameters.
         */
        std::vector<double> distortion_parameters() const override;

        /**
         * Initialize the object from a set of distortion parameters.
         */
        void set_distortion_parameters( const std::vector<double>& params ) override;

        /**
         * Number of distortion parameters
         */
        int num_dist_params() const override;

        /**
         * Each derived model needs to have a string name.
         */
        std::string name() const override;
    
        /**
         * Used to scale distortion with image size
         */
        ImageResult<void> scale( double scale ) override;

}; // End of Distortion_Null class

} // End of tmns::geo::cam namespace