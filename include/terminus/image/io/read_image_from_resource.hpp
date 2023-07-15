/**
 * @file    read_image_from_resource.hpp
 * @author  Marvin Smith
 * @date    7/12/2023
*/
#pragma once

// External Terminus Libraries
#include <terminus/math/Rectangle.hpp>

// Terminus Libraries
#include "../error/ErrorCategory.hpp"
#include "../Image_Base.hpp"

namespace tmns::image::io {

/************************************************/
/*          Read image from Disk Resource       */
/************************************************/
template <typename PixelT>
ImageResult<Image_Memory<PixelT>> read_image_from_resource( const Read_Image_Resource_Disk::ptr_t resource,
                                                            const math::Rect2i&                   bbox )
{
    // Create output image
    Image_Memory<PixelT> output_image;
    auto size_res = output_image.set_size( bbox.width(),
                                           bbox.height() );
    if( size_res.has_error() )
    {
        return outcome::fail( size_res.error() );
    }

    // Pass the image data
    auto load_res = resource->read( output_image.buffer(),
                                    bbox );

    if( load_res.has_error() )
    {
        return outcome::fail( load_res.error() );
    }
    else
    {
        return outcome::ok<Image_Memory<PixelT>>( std::move( output_image ) );
    }
}

/************************************************/
/*          Read image from Disk Resource       */
/************************************************/
template <typename PixelT>
ImageResult<Image_Memory<PixelT>> read_image_from_resource( const Read_Image_Resource_Disk::ptr_t resource )
{
    return read_image_from_resource<PixelT>( resource,
                                             math::Rect2i( 0, 0,
                                                           resource->cols(),
                                                           resource->rows() ) );
}

} // end of tmns::image::io namespace