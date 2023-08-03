/**
 * @file    detect_interest_points.hpp
 * @author  Marvin Smith
 * @date    7/20/2023
*/
#pragma once

// C++ Lib

namespace tmns::feature {

/**
 * Preform feature detection on an image, returning the KeyPoints
 */
ImageResult<std::vector<KeyPoint>> detect_interest_points( const Image_Base<ImageT>&              image,
                                                           const FeatureDetectorConfigBase::ptr_t fd_config = DEFAULT_DETECTOR_CONFIG(),
                                                           const core::Session_Context&           session_context )
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

} // End of tmns::feature namespace