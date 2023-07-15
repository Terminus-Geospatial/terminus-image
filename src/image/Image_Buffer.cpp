/**
 * @file    Image_Buffer.cpp
 * @author  Marvin Smith
 * @date    7/14/2023
*/
#include "Image_Buffer.hpp"

// Terminus Libraries
#include "pixel/Channel_Type_Enum.hpp"
#include "pixel/Pixel_Format_Enum.hpp"

namespace tmns::image {

/********************************/
/*          Constructor         */
/********************************/
Image_Buffer::Image_Buffer( Image_Format format,
                            void*        data )
 : m_data( data ),
   m_format( std::move( format ) ),
   m_cstride( channel_size_bytes( format.channel_type() ).assume_value() *
              num_channels( format.pixel_type() ).assume_value() ),
   m_rstride( m_cstride * format.cols() ),
   m_pstride( m_rstride * format.rows() )
   {}

/************************************/
/*          Get Buffer Cols         */
/************************************/
size_t Image_Buffer::cols() const
{
    return m_format.cols();
}

/************************************/
/*          Get Buffer Rows         */
/************************************/
size_t Image_Buffer::rows() const
{
    return m_format.rows();
}

} // end tmns::image