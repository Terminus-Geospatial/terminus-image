/**
 * @file    Distortion_Brown_Conrady.hpp
 * @author Marvin Smith
 * @date 11/10/2023
*/
#pragma once

// Terminus Libraries
#include <terminus/geography/camera/Distortion_Base.hpp>

namespace tmns::geo::cam {

/**
 * @class Distortion_Brown_Conrady
 * 
 * Implements the Brown-Conrady distortion model.
*/
class Distortion_Brown_Conrady : public Distortion_Base
{
    public:

        /**
         * Default Constructor
         */
        Distortion_Brown_Conrady();

        /**
         * Parameters in a single array
         */
        Distortion_Brown_Conrady( const std::vector<double>& params );

        /**
         * Separated Parameters
         */
        Distortion_Brown_Conrady( const math::Point2d&       principle_point_pitch,
                                  const std::vector<double>& radial_distortion,
                                  const std::vector<double>& tangential_distortion,
                                  double                     tangential_distortion_angle_rad );
        
        /**
         * Convert from Undistorted to Distorted pixel coordinates
         */
        math::Point2d to_distorted( const std::shared_ptr<Camera_Model_Pinhole> camera_model,
                                    const math::Point2d&                        pixel_coord ) const override;

        /**
         * Convert from Distorted to Undistorted pixel coordinates
         */
        math::Point2d to_undistorted( const std::shared_ptr<Camera_Model_Pinhole> camera_model,
                                      const math::Point2d&                        pixel_coord ) const override;

        /**
         * Return true if the to_distorted() implementation does not use a solver.
         */
        bool has_fast_distort() const override;
    
        /**
         * Return true if the undistorted_coordinates() implementation does not use a solver.
         */
        bool has_fast_undistort() const override;

        /**
         * Get the distortion parameters
         */
        std::vector<double> distortion_parameters() const override;

        /**
         * Set the list of distortion parameters
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

    private:

        /// Principle Point
        math::Point2d m_principle_point { { 0, 0 } };

        /// Radial Distortion
        math::Vector3d m_radial_distortion { { 0, 0, 0 } };

        /// Centering Distortion
        math::Vector2d m_centering_distortion { { 0, 0 } };

        /// Centering Angle (Phi)
        double m_centering_angle_rad { 0 };

}; // End of Distortion_Brown_Conrady class

} // End of tmns::geo::cam namespace