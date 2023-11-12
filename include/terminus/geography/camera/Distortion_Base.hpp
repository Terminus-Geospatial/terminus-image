/**
 * @file    Distortion_Base.hpp
 * @author  Marvin Smith
 * @date    11/9/2023
*/
#pragma once

// Terminus Libraries
#include <terminus/math/Point.hpp>

// C++ Libraries
#include <memory>

namespace tmns::geo::cam {

// Pre-define the Camera model class
class Camera_Model_Pinhole;

class Distortion_Base
{
    public:

        // Underlying Pointer Type
        using ptr_t = std::unique_ptr<Distortion_Base>;

        /**
         * Destructor
        */
        virtual ~Distortion_Base() = default;

        virtual math::Point2d to_distorted( const std::shared_ptr<Camera_Model_Pinhole> camera_model,
                                            const math::Point2d&                        pixel_coord ) const;

        virtual math::Point2d to_undistorted( const std::shared_ptr<Camera_Model_Pinhole> camera_model,
                                              const math::Point2d&                        pixel_coord ) const;

        /**
         * Return true if the to_distorted() implementation does not use a solver.
         */
        virtual bool has_fast_distort  () const;
    
        /**
         * Return true if the undistorted_coordinates() implementation does not use a solver.
         */
        virtual bool has_fast_undistort() const;

        /**
         * Return a vector containing all the distortion parameters.
         */
        virtual std::vector<double> distortion_parameters() const;

        /**
         * Initialize the object from a set of distortion parameters.
         */
        virtual void set_distortion_parameters( const std::vector<double>& params );

        /**
         * Number of distortion parameters
         */
        virtual int num_dist_params() const = 0;

        /**
         * Each derived model needs to have a string name.
         */
        virtual std::string name() const = 0;
    
        /**
         * Used to scale distortion with image size
         */
        virtual ImageResult<void> scale( double scale ) = 0;
    
        /// Used to scale distortion with image size
        std::vector<std::string> distortion_param_names() const { return m_distortion_param_names; }

    protected:

        std::vector<std::string> m_distortion_param_names;

}; // End of Distortion_Base class

} // End of tmns::geo::cam namespace