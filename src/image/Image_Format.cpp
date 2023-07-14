/**
 * @file    Image_Format.cpp
 * @author  Marvin Smith
 * @date    7/13/2023
*/
#include "Image_Format.hpp"

namespace tmns::image {

/************************************************************/
/*   Check if the image format object is fully structured   */
/************************************************************/
bool Image_Format::complete() const
{
    return ( m_rows > 0 &&
             m_cols > 0 &&
             m_channels > 0 &&
             !channel_size_bytes( m_channel_type ).has_error() &&
             !num_channels( m_pixel_type ).has_error() );
}


} // end of tmns::image namespace