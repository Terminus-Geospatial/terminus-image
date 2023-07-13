/**
 * @file    Image_Resource_Base.hpp
 * @author  Marvin Smith
 * @date    7/12/2023
*/
#pragma once

namespace tmns::warp::io {

class Image_Write_Resource
{
    public:

        /// @brief  Destructor
        virtual ~Image_Write_Resource() = default;

        virtual error::Result<> write( Image_Buffer const& buf,
                                       math::BBox2i const& bbox ) = 0;


}; // End of Image_Write_Resource Class


/**
 * Resource which can load and save an image
*/
class Image_Resource_Base : public Image_Read_Resource, Image_Write_Resource {};

} // end of tmns::warp::io namespace