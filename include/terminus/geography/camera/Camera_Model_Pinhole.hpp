/**
 * @file    Camera_Model_Pinhole.hpp
 * @author  Marvin Smith
 * @date    11/9/2023
*/
#pragma once

// Terminus Libraries
#include <terminus/geography/camera/Camera_Model_Base.hpp>
#include <terminus/geography/camera/Distortion_Base.hpp>
#include <terminus/geography/camera/Distortion_Null.hpp>
#include <terminus/math/Point.hpp>
#include <terminus/math/Size.hpp>

// C++ Libraries
#include <array>
#include <vector>

namespace tmns::geo::cam {

/**
 * Camera model for the Brown-Conrady camera
*/
class Camera_Model_Pinhole : public Camera_Model_Base
{
    public:

        Camera_Model_Pinhole();

        /**
         * Constructor
         */
        Camera_Model_Pinhole( const std::optional<math::Point3d>& camera_center,
                              const math::Point2d&                focal_length_pitch,
                              const math::Point2d&                principle_point_pitch,
                              const math::Vector3d&               x_axis_direction,
                              const math::Vector3d&               y_axis_direction,
                              const math::Vector3d&               z_axis_direction,
                              double                              pitch      = 1.0,
                              Distortion_Base::ptr_t              distortion = nullptr );
        
        /**
         * Destructor
         */
        ~Camera_Model_Pinhole() override = default;

        /**
         * Transform a coordinate from 3d cartesian into pixel coordinates.  Pixel coordinates are 2-dimensional values
         * in real (aka floating-point) representation.  This allows for sub-pixel accuracy.  To get an indexible conversion,
         * simply convert to an integer space noting if the "center" is the top-left or center. 
         */
        ImageResult<math::Point2d> point_to_pixel( const math::Point3d& point ) const override;


        /**
         * Transform a coordinate from 2d pixel space into a (likely) unit-length vector in 3D space from the origin of the
         * sensor.  
         */
        ImageResult<math::Vector3d> pixel_to_vector( const math::Point2d& pixel ) const override;

        /**
         * Get the camera origin in the frame of reference of the camera model.  This method is often used to
         * find the origin of a ray emanating from the focal point of the camera through a pixel on the image
         * plane (e.g. for computing ray-ray intersection in a stereo vision algorithm).
         * - Generally the input pixel is only used for linescan cameras.
         */
        ImageResult<math::Point3d> camera_origin( const math::Point2d& pixel ) const override;

        /**
         * Get the "type" string for the specified camera-model.  These must be unique amongst registered camera-model
         * types.
         */
        std::string type() const override;

        /**
         * Get the pose, represented as a quaternion, for the camera at a particular pixel.
         * It represents the rotation from the camera frame to the world frame.  
         * - The input pixel will likely only be used for linescan cameras.
         */
        ImageResult<math::Quaternion> camera_pose( const math::Point2d& pixel ) const override;

        /**
         * Print a human-readable output of the camera configuration
         */
        std::string to_string( size_t offset ) const override;

    private:

        /// Origin of the camera in cartesian
        std::optional<math::Point3d> m_camera_origin;

        /// Focal Length
        math::Point2d  m_focal_length_pitch { { 0, 0 } };

        /// Principle Point
        math::Point2d   m_principle_point_pitch { { 0, 0 } };

        /// Axis Directions
        math::Vector3d m_x_axis { { 1, 0, 0 } };
        math::Vector3d m_y_axis { { 0, 1, 0 } };
        math::Vector3d m_z_axis { { 0, 0, 1 } };

        /// Pitch Parameters
        double m_pitch { 0 };

        // Distortion Values
        geo::cam::Distortion_Base::ptr_t m_distortion;

}; // End of Camera_Model_Pinhole class

} // End of tmns::geo::cam namespace