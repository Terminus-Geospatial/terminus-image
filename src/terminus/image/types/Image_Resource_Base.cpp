/**
 * @file    Image_Resource_Base.cpp
 * @author  Marvin Smith
 * @date    7/14/2023
*/
#include "Image_Resource_Base.hpp"

namespace tmns::image {

/****************************************************/
/*          Get the number of image columns         */
/****************************************************/
size_t Read_Image_Resource_Base::cols() const
{
    return format().cols();
}

/*************************************************/
/*          Get the number of image rows         */
/*************************************************/
size_t Read_Image_Resource_Base::rows() const
{
    return format().rows();
}

/****************************************************/
/*          Get the number of image planes          */
/****************************************************/
size_t Read_Image_Resource_Base::planes() const
{
    return format().planes();
}

/********************************************************/
/*          Get the number of image channels            */
/********************************************************/
size_t Read_Image_Resource_Base::channels() const
{
    return num_channels( pixel_type() ).assume_value();
}

/************************************************/
/*          Get an image bounding box           */
/************************************************/
math::Rect2i Read_Image_Resource_Base::full_bbox() const
{
    return math::Rect2i( 0, 0, cols(), rows() );
}

/************************************************/
/*          Get the Pixel Format Type           */
/************************************************/
Pixel_Format_Enum Read_Image_Resource_Base::pixel_type() const
{
    return format().pixel_type();
}

/****************************************/
/*          Get the Channel Type        */
/****************************************/
Channel_Type_Enum Read_Image_Resource_Base::channel_type() const
{
    return format().channel_type();
}

} // End of tmns::image namespace