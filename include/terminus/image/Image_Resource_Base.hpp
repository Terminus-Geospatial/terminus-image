/**
 * @file    Image_Resource_Base.hpp
 * @author  Marvin Smith
 * @date    7/12/2023
*/
#pragma once

/// External Terminus Libraries
#include <terminus/math/Rectangle.hpp>

/// Terminus Libraries
#include "Image_Buffer.hpp"

namespace tmns::image {

class Image_Read_Resource
{

}; // End of Image_Read_Resource Class

class Image_Write_Resource
{
    public:

        /// @brief  Destructor
        virtual ~Image_Write_Resource() = default;

        virtual ImageResult<void> write( const Image_Buffer& buf,
                                         const math::Rect2i& bbox ) = 0;


}; // End of Image_Write_Resource Class

/**
 * Resource which can load and save an image
*/
class Image_Resource_Base : public Image_Read_Resource, Image_Write_Resource {};

} // end of tmns::image namespace