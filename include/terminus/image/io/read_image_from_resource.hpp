/**
 * @file    read_image_from_resource.hpp
 * @author  Marvin Smith
 * @date    7/12/2023
*/
#pragma once

// Terminus Libraries
#include "../error/ErrorCategory.hpp"
#include "../Image_Base.hpp"

namespace tmns::image::io {


template <class ImageT>
error::Result<ImageViewBase<ImageT>> read_image_from_resource( const Image_Resource_Base& resource )
{
    return read_image_from_resource( resource,
                                     math::BBox2i( 0, 0, src.cols(), src.rows() ) );
}


} // end of tmns::image::io namespace