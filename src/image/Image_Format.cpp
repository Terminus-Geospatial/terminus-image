/**
 * @file    Image_Format.cpp
 * @author  Marvin Smith
 * @date    7/13/2023
*/
#include "Image_Format.hpp"

namespace tmns::image {

/********************************/
/*          Constructor         */
/********************************/
Image_Format::Image_Format( size_t            cols,
                            size_t            rows,
                            size_t            planes,
                            Pixel_Format_Enum pixel_type,
                            Channel_Type_Enum channel_type,
                            bool              premultiply )
  : m_cols( cols ),
    m_rows( rows ),
    m_planes( planes ),
    m_pixel_type( pixel_type ),
    m_channel_type( channel_type ),
    m_premultiply( premultiply )
{
}

/********************************/
/*          Image Cols          */
/********************************/
size_t Image_Format::cols() const
{
    return m_cols;
}

/********************************/
/*          Image Rows          */
/********************************/
size_t Image_Format::rows() const
{
    return m_rows;
}

/************************************/
/*          Image Planes            */
/************************************/
size_t Image_Format::planes() const
{
    return m_planes;
}

/********************************/
/*          Pixel Type          */
/********************************/
Pixel_Format_Enum Image_Format::pixel_type() const
{
    return m_pixel_type;
}

/************************************/
/*          Channel Type            */
/************************************/
Channel_Type_Enum Image_Format::channel_type() const
{
    return m_channel_type;
}

/****************************************/
/*          Check if premultiply        */
/****************************************/
bool Image_Format::premultiply() const
{
    return m_premultiply;
}

/************************************************************/
/*   Check if the image format object is fully structured   */
/************************************************************/
bool Image_Format::complete() const
{
    return ( m_rows > 0 &&
             m_cols > 0 &&
             m_planes > 0 &&
             !channel_size_bytes( m_channel_type ).has_error() &&
             !num_channels( m_pixel_type ).has_error() );
}


} // end of tmns::image namespace