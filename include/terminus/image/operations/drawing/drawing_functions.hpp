/**
 * @file    draw_line.hpp
 * @author  Marvin Smith
 * @date    8/13/2023
*/
#pragma once

// Terminus Libraries
#include <terminus/math/Point.hpp>

// Terminus Image Libraries
#include "../blob/Sparse_Image_View.hpp"
#include "../blob/Uniform_Blob.hpp"
#include "compute_line_points.hpp"

// C++ Libraries
#include <deque>

namespace tmns::image::ops {

/**
 * Draw a line on the image
 * 
 * @param input_image
 * @param p1
 * @param p2
 * @param color
 * @param thickness
 * 
 * @returns Image with line drawn on it.
*/
template <typename ImageT>
blob::Sparse_Image_View<ImageT,blob::Uniform_Blob<typename ImageT::pixel_type>> 
        draw_line( const ImageT&                      input_image,
                   const tmns::math::Point2i&         p1,
                   const tmns::math::Point2i&         p2,
                   const typename ImageT::pixel_type& color,
                   int                                thickness )
{
    typedef typename ImageT::pixel_type PixelT;


    // Construct list of coordinates
    auto uniform_blob = std::make_shared<blob::Uniform_Blob<PixelT>>( color );
    Line_Overlap_Mode overlap_mode = Line_Overlap_Mode::BOTH;
    auto res = drawing::compute_line_points( p1,
                                             p2,
                                             color,
                                             thickness,
                                             overlap_mode,
                                             uniform_blob );

    // Build the Sparse Image View
    std::deque<std::shared_ptr<blob::Uniform_Blob<PixelT>>> blobs;
    blobs.push_back( uniform_blob );

    return blob::Sparse_Image_View<ImageT,
                                   blob::Uniform_Blob<PixelT>>( input_image, 
                                                                blobs );
}

} // End of tmns::image::ops namespace