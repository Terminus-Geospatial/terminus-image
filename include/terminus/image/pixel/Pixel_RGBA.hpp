/**
 * @file    Pixel_RGBA.hpp
 * @author  Marvin Smith
 * @date    7/16/2023
*/
#pragma once

// Terminus Libraries
#include "Channel_Types.hpp"
#include "Pixel_Base.hpp"

// C++ Libraries
#include <array>

namespace tmns::image {

/**
 * RGBA PixelType
*/
template <typename ChannelT>
class Pixel_RGBA : public Pixel_Base<ChannelT>
{
    public:

        typedef ChannelT channel_type;
        typedef typename ChannelT::data_type data_type;

        /**
         * Default Constructor
        */
        Pixel_RGBA() = default;

        /**
         * Set all channels to the same luminance value
        */
        Pixel_RGBA( const data_type& pix )
        {
            std::copy( m_data, m_data + 3, pix );
        }

        /**
         * Set all channels independently
        */
        Pixel_RGBA( const data_type& r,
                    const data_type& g,
                    const data_type& b,
                    const data_type& a )
        {
            m_data[0] = r;
            m_data[1] = g;
            m_data[2] = b;
            m_data[3] = a;
        }

        /// Number of channels
        static constexpr int NUM_CHANNELS = 4;

    private:

        /// Underlying Pixel Data
        std::array<data_type,4> m_data{ 0, 0, 0, 0 };

}; // End of Pixel_RGB Class

/// Aliases for easier typing
using PixelRGBA_u8  = Pixel_RGBA<ChannelType_u8>;
using PixelRGBA_u12 = Pixel_RGBA<ChannelType_u12>;
using PixelRGBA_u14 = Pixel_RGBA<ChannelType_u14>;
using PixelRGBA_u16 = Pixel_RGBA<ChannelType_u16>;

using PixelRGBA_f64  = Pixel_RGBA<ChannelType_f64>;
using PixelRGBA_f64f = Pixel_RGBA<ChannelType_f64f>;

} // End of tmns::image namespace