/**
 * @file    Pixel_RGB.hpp
 * @author  Marvin Smith
 * @date    7/11/2023
*/
#pragma once

// Terminus Libraries
#include "Pixel_Base.hpp"

namespace tmns::warp::image {

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
        ChannelT m_data[3] { 0, 0, 0 };

}; // End of Pixel_RGB Class

} // End of tmns::warp::image namespace