/**
 * @file    Pixel_RGB.hpp
 * @author  Marvin Smith
 * @date    7/11/2023
*/
#pragma once

// Terminus Libraries
#include "Channel_Types.hpp"
#include "Pixel_Base.hpp"

namespace tmns::image {

/**
 * RGB PixelType
*/
template <typename ChannelT>
class Pixel_RGB : public Pixel_Base<ChannelT>
{
    public:

        /**
         * Default Constructor
        */
        Pixel_RGB() = default;

        /**
         * Set all channels to the same luminance value
        */
        Pixel_RGB( const ChannelT& pix )
        {
            std::copy( m_data, m_data + 3, pix );
        }

        /**
         * Set all channels independently
        */
        Pixel_RGB( const ChannelT& r,
                   const ChannelT& g,
                   const ChannelT& b )
        {
            m_data[0] = r;
            m_data[1] = g;
            m_data[2] = b;
        }

    private:

        /// Underlying Pixel Data
        typename ChannelT::data_type m_data[3] { 0, 0, 0 };

}; // End of Pixel_RGB Class

/// Aliases for easier typing
using PixelRGB_u8  = Pixel_RGB<ChannelType_u8>;
using PixelRGB_u12 = Pixel_RGB<ChannelType_u12>;

} // End of tmns::image namespace