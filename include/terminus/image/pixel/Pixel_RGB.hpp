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

/**
 * Per Fundamental_Types.hpp, we need to register our
 * compound types.  See header for details
*/
template <typename ChannelT>
struct Compound_Channel_Type<Pixel_RGB<ChannelT> >
{
    typedef ChannelT type;
}; // End of Compound_Channel_Type<> Struct

template <typename ChannelT>
struct Compound_Channel_Count<Pixel_RGB<ChannelT>>
{
    static const size_t value = Pixel_RGB<ChannelT>::NUM_CHANNELS;
}; // End of Compound_Channel_Count<> Struct

template <typename OldChannelT, typename NewChannelT>
struct Compound_Channel_Cast<Pixel_RGB<OldChannelT>, NewChannelT>
{
    typedef Pixel_RGB<NewChannelT> type;
}; // End of Compound_Channel_Cast<> structure

template <typename OldChannelT, typename NewChannelT>
struct Compound_Channel_Cast<Pixel_RGB<OldChannelT>, const NewChannelT>
{
    typedef const Pixel_RGB<NewChannelT> type;
}; // End of Compound_Channel_Cast<> structure

/// Aliases for easier typing
using PixelRGB_u8  = Pixel_RGB<ChannelType_u8>;
using PixelRGB_u12 = Pixel_RGB<ChannelType_u12>;
using PixelRGB_u14 = Pixel_RGB<ChannelType_u14>;
using PixelRGB_u16 = Pixel_RGB<ChannelType_u16>;

using PixelRGB_f32  = Pixel_RGB<ChannelType_f32>;
using PixelRGB_f32f = Pixel_RGB<ChannelType_f32f>;
using PixelRGB_f64  = Pixel_RGB<ChannelType_f64>;
using PixelRGB_f64f = Pixel_RGB<ChannelType_f64f>;

} // End of tmns::image namespace