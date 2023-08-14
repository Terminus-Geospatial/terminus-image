/**
 * @file    Pixel_RGBA.hpp
 * @author  Marvin Smith
 * @date    7/16/2023
*/
#pragma once

// Terminus Libraries
#include "../types/Compound_Types.hpp"
#include "Channel_Range.hpp"
#include "Pixel_Base.hpp"

// C++ Libraries
#include <array>

namespace tmns::image {

/**
 * RGBA PixelType
*/
template <typename ChannelT>
class Pixel_RGBA : public Pixel_Base<Pixel_RGBA<ChannelT>>
{
    public:

        typedef ChannelT channel_type;

        /**
         * Default Constructor
        */
        Pixel_RGBA() = default;

        /**
         * Set all channels to the same luminance value
        */
        Pixel_RGBA( const channel_type& pix )
        {
            m_data.fill( pix );
        }

        /**
         * Set all channels independently
        */
        Pixel_RGBA( const channel_type& r,
                    const channel_type& g,
                    const channel_type& b,
                    const channel_type& a )
        {
            m_data[0] = r;
            m_data[1] = g;
            m_data[2] = b;
            m_data[3] = a;
        }

        /**
         * Convert channel-types
         */
        template <typename OtherChannelT>
        explicit Pixel_RGBA( const Pixel_RGBA<OtherChannelT>& other )
        {
            for( size_t i = 0; i < 4; i++ )
            {
                m_data[i] = ChannelT( other[i] );
            }
        }

        /**
         * Get the pixel at the specified location
        */
        const channel_type& operator[]( size_t idx ) const
        {
            return m_data[idx];
        }

        /**
         * Get the pixel reference at the specified location
        */
        channel_type& operator[]( size_t idx )
        {
            return m_data[idx];
        }

        /**
         * Send an all white pixel back
        */
        static Pixel_RGBA<ChannelT> max()
        {
            return Pixel_RGBA<ChannelT>( ChannelT::MAX_VALUE );
        }

        /// Number of channels
        static constexpr int NUM_CHANNELS = 4;

        static std::string class_name()
        {
            return "Pixel_RGBA<" + ChannelT::name() + ">";
        }

    private:

        /// Underlying Pixel Data
        std::array<channel_type,4> m_data{ 0, 0, 0, 0 };

}; // End of Pixel_RGBA Class

/**
 * Per Fundamental_Types.hpp, we need to register our
 * compound types.  See header for details
*/
template <typename ChannelT>
struct Compound_Channel_Type<Pixel_RGBA<ChannelT> >
{
    typedef ChannelT type;
}; // End of Compound_Channel_Type<> Struct

template <typename ChannelT>
struct Compound_Channel_Count<Pixel_RGBA<ChannelT>>
{
    static const size_t value = Pixel_RGBA<ChannelT>::NUM_CHANNELS;
}; // End of Compound_Channel_Count<> Struct

template <typename OldChannelT, typename NewChannelT>
struct Compound_Channel_Cast<Pixel_RGBA<OldChannelT>, NewChannelT>
{
    typedef Pixel_RGBA<NewChannelT> type;
}; // End of Compound_Channel_Cast<> structure

template <typename OldChannelT, typename NewChannelT>
struct Compound_Channel_Cast<Pixel_RGBA<OldChannelT>, const NewChannelT>
{
    typedef const Pixel_RGBA<NewChannelT> type;
}; // End of Compound_Channel_Cast<> structure


/// Aliases for easier typing
using PixelRGBA_u8  = Pixel_RGBA<uint8_t>;
using PixelRGBA_u16 = Pixel_RGBA<uint16_t>;

using PixelRGBA_f32  = Pixel_RGBA<float>;
using PixelRGBA_f64  = Pixel_RGBA<double>;

} // End of tmns::image namespace