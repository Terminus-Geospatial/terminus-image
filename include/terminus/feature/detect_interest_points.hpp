/**
 * @file    detect_interest_points.hpp
 * @author  Marvin Smith
 * @date    7/20/2023
*/
#pragma once

// Terminus Libraries
#include <terminus/core/Session_Context.hpp>

// C++ Libraries

namespace tmns::feature {

/**
 * Perform feature detection on an image, returning the interest points
 */
template <typename ImageT>
ImageResult<std::vector<Interest_Point>> detect_interest_points( const Image_Base<ImageT>&     image,
                                                                 const Detector_Base::ptr_t    detector,
                                                                 const core::Session_Context&  session_context )
{
    // Create a Feature Extraction Service
    auto feature_detector = FeatureDetectorFactory::create( fd_config );

    // Build work queue for dispatching work
    auto thread_pool = std::make_unique<core::Ordered_Work_Queue>( session_context );

    // Subdivide work by tile size
    auto tile_size =
    if( fd_config->enforce_tile_size() )
    {

    }
}

/**
 * Run the detector, but store the keypoints within the image
*/
template <typename ImageT>
ImageResult<void> detect_interest_points( Image_Base<ImageT>& image,
                                          std::string         detector_driver,
                                          const core::Session_Context& session_context = core::Session_Context::GREEDY() )
{

} // End of detect_interest_points method

} // End of tmns::feature namespace