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

        typedef ChannelT channel_type;
        typedef typename ChannelT::data_type data_type;

        /**
         * Default Constructor
        */
        Pixel_RGB() = default;

        /**
         * Set all channels to the same luminance value
        */
        Pixel_RGB( const data_type& pix )
        {
            std::copy( m_data, m_data + 3, pix );
        }

        /**
         * Set all channels independently
        */
        Pixel_RGB( const data_type& r,
                   const data_type& g,
                   const data_type& b )
        {
            m_data[0] = r;
            m_data[1] = g;
            m_data[2] = b;
        }

        static std::string class_name()
        {
            return "Pixel_RGB<" + ChannelT::name() + ">";
        }

        /// Number of channels
        static constexpr int NUM_CHANNELS = 3;

    private:

        /// Underlying Pixel Data
        std::array<data_type,3> m_data{ 0, 0, 0 };

}; // End of Pixel_RGB Class

/// Aliases for easier typing
using PixelRGB_u8  = Pixel_RGB<ChannelType_u8>;
using PixelRGB_u12 = Pixel_RGB<ChannelType_u12>;
using PixelRGB_u14 = Pixel_RGB<ChannelType_u14>;
using PixelRGB_u16 = Pixel_RGB<ChannelType_u16>;

} // End of tmns::image namespace