/**
 * @file    Pixel_Format_ID.hpp
 * @author  Marvin Smith
 * @date    7/14/2023
*/
#pragma once

// Terminus Libraries
#include "Pixel_Format_Enum.hpp"
#include "Pixel_RGB.hpp"
#include "Pixel_RGBA.hpp"

namespace tmns::image {

/**
 * Simple class for converting a formal Pixel-Type into a Pixel-Type-Enum
*/
template <typename PixelT>
struct Pixel_Format_ID
{
    static const Pixel_Format_Enum value = Pixel_Format_Enum::UNKNOWN;
    static const int num_channels = { -1 };

}; // End of Pixel_Format_ID Class

/// Lookups
template <typename ChannelT> struct Pixel_Format_ID<Pixel_RGB<ChannelT>>
{
    static const Pixel_Format_Enum value = Pixel_Format_Enum::RGB;
    static const int num_channels = 3;
};

template <typename ChannelT> struct Pixel_Format_ID<Pixel_RGBA<ChannelT>>
{
    static const Pixel_Format_Enum value = Pixel_Format_Enum::RGBA;
    static const int num_channels = 4;
};

} // end of tmns::image namespace