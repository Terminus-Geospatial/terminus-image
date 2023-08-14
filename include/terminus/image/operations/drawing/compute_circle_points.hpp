/**
 * @file    compute_circle_points.hpp
 * @author  Marvin Smith
 * @date    8/13/2023
*/
#pragma once

// Terminus Libraries
#include <terminus/log/utility.hpp>
#include <terminus/math/Point.hpp>
#include <terminus/math/Size.hpp>

// Terminus Image Libraries
#include "Drawing_Enums.hpp"

namespace tmns::image::ops::drawing {

/**
 * Return a list of pixel coordinates representing the circle to draw
*/
template <typename PixelT>
ImageResult<void> compute_circle_points( const tmns::math::Point2i&                  center,
                                         int                                         radius,
                                         const PixelT&                               color,
                                         int                                         thickness,
                                         std::shared_ptr<blob::Uniform_Blob<PixelT>> output )
{
    tmns::log::trace( ADD_CURRENT_LOC(),
                      "Start of Method.\n  Center: ", 
                      center.to_string(),
                      "\n  Radius: ", 
                      radius,
                      "\n  Thickness: ",
                      thickness );

    // Make sure blob is initialized
    if( !output )
    {
        output = std::make_shared<blob::Uniform_Blob<PixelT>>( color );
    }

    // Create output
    output->clear();
    
    // Break circle into 

    return tmns::outcome::ok();
}


} // End of tmns::image::ops::drawing namespace