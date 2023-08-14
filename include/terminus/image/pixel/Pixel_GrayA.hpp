/**
 * @file    Pixel_GrayA.hpp
 * @author  Marvin Smith
 * @date    7/30/2023
*/
#pragma once

// Terminus Image Libraries
#include "../types/Compound_Types.hpp"
#include "Pixel_Base.hpp"

namespace tmns::image {

/**
 * Grayscale w/ Alpha Pixeltype
*/
template <typename ChannelT>
class Pixel_GrayA : public Pixel_Base<Pixel_GrayA<ChannelT>>
{
    public:

        typedef ChannelT channel_type;
        typedef typename ChannelT::data_type data_type;

        /**
         * Default Constructor
        */
        Pixel_GrayA() = default;

        /**
         * Set pixel value to input, and alpha to max
        */
        Pixel_GrayA( const data_type& pix )
          : m_data{ pix, ChannelT::MAX_VALUE }
        {}

        /**
         * Set pixel and alpha
        */
        Pixel_GrayA( const data_type& pix,
                     const data_type& alpha )
          : m_data{ pix, alpha }
        {}

        /// Number of channels
        static constexpr int NUM_CHANNELS = 2;

        static std::string class_name()
        {
            return "Pixel_GrayA<" + ChannelT::name() + ">";
        }

    private:

        /// Underlying Pixel Data
        std::array<data_type,2> m_data{ 0, 0 };

}; // End of Pixe_GrayA Class

/**
 * Per Fundamental_Types.hpp, we need to register our
 * compound types.  See header for details
*/
template <typename ChannelT>
struct Compound_Channel_Type<Pixel_GrayA<ChannelT> >
{
    typedef ChannelT type;
}; // End of Compound_Channel_Type<> Struct

template <typename ChannelT>
struct Compound_Channel_Count<Pixel_GrayA<ChannelT>>
{
    static const size_t value = Pixel_Gray<ChannelT>::NUM_CHANNELS;
}; // End of Compound_Channel_Count<> Struct

template <typename OldChannelT, typename NewChannelT>
struct Compound_Channel_Cast<Pixel_GrayA<OldChannelT>, NewChannelT>
{
    typedef Pixel_Gray<NewChannelT> type;
}; // End of Compound_Channel_Cast<> structure

template <typename OldChannelT, typename NewChannelT>
struct Compound_Channel_Cast<Pixel_GrayA<OldChannelT>, const NewChannelT>
{
    typedef const Pixel_Gray<NewChannelT> type;
}; // End of Compound_Channel_Cast<> structure


/// Aliases for easier typing
using PixelGrayA_u8  = Pixel_GrayA<uint8_t>;
using PixelGrayA_u16 = Pixel_GrayA<uint16_t>;
using PixelGrayA_u32 = Pixel_GrayA<uint32_t>;
using PixelGrayA_u64 = Pixel_GrayA<uint64_t>;

using PixelGrayA_f32  = Pixel_GrayA<float>;
using PixelGrayA_f64  = Pixel_GrayA<double>;

} // End of tmns::image namespace