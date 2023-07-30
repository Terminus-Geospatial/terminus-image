/**
 * @file    Pixel_Gray.hpp
 * @author  Marvin Smith
 * @date    7/29/2023
*/
#pragma once

// Terminus Image Libraries
#include "../types/Compound_Types.hpp"
#include "Channel_Types.hpp"
#include "Pixel_Base.hpp"

namespace tmns::image {

/**
 * Grayscale Pixeltype
*/
template <typename ChannelT>
class Pixel_Gray : public Pixel_Base<ChannelT>
{
    public:

        typedef ChannelT channel_type;
        typedef typename ChannelT::data_type data_type;

        /**
         * Default Constructor
        */
        Pixel_Gray() = default;

        /**
         * Set all channels to the same luminance value
        */
        Pixel_Gray( const data_type& pix )
          : m_data( pix )
        {}

        /// Number of channels
        static constexpr int NUM_CHANNELS = 1;

        static std::string class_name()
        {
            return "Pixel_Gray<" + ChannelT::name() + ">";
        }

    private:

        /// Underlying Pixel Data
        data_type m_data{ 0 };

}; // End of Pixe_Gray Class

/**
 * Per Fundamental_Types.hpp, we need to register our
 * compound types.  See header for details
*/
template <typename ChannelT>
struct Compound_Channel_Type<Pixel_Gray<ChannelT> >
{
    typedef ChannelT type;
}; // End of Compound_Channel_Type<> Struct

template <typename ChannelT>
struct Compound_Channel_Count<Pixel_Gray<ChannelT>>
{
    static const size_t value = Pixel_Gray<ChannelT>::NUM_CHANNELS;
}; // End of Compound_Channel_Count<> Struct

template <typename OldChannelT, typename NewChannelT>
struct Compound_Channel_Cast<Pixel_Gray<OldChannelT>, NewChannelT>
{
    typedef Pixel_Gray<NewChannelT> type;
}; // End of Compound_Channel_Cast<> structure

template <typename OldChannelT, typename NewChannelT>
struct Compound_Channel_Cast<Pixel_Gray<OldChannelT>, const NewChannelT>
{
    typedef const Pixel_Gray<NewChannelT> type;
}; // End of Compound_Channel_Cast<> structure


/// Aliases for easier typing
using PixelGray_u8  = Pixel_Gray<ChannelType_u8>;
using PixelGray_u12 = Pixel_Gray<ChannelType_u12>;
using PixelGray_u14 = Pixel_Gray<ChannelType_u14>;
using PixelGray_u16 = Pixel_Gray<ChannelType_u16>;

using PixelGray_f32  = Pixel_Gray<ChannelType_f32>;
using PixelGray_f32f = Pixel_Gray<ChannelType_f32f>;
using PixelGray_f64  = Pixel_Gray<ChannelType_f64>;
using PixelGray_f64f = Pixel_Gray<ChannelType_f64f>;

} // End of tmns::image namespace