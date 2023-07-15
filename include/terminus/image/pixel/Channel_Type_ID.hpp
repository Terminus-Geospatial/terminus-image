/**
 * @file    Channel_Type_ID.hpp
 * @author  Marvin Smith
 * @date    7/14/2023
*/
#pragma once

// Terminus Libraries
#include "Channel_Type_Enum.hpp"
#include "Channel_Types.hpp"

namespace tmns::image {

/**
 * Simple structure for mapping channel-types to Channel_Type_Enum objects
*/
template <class ChannelT>
struct Channel_Type_ID
{
    static constexpr Channel_Type_Enum value = Channel_Type_Enum::UNKNOWN;
};

template <> struct Channel_Type_ID<ChannelType_u8>{  static constexpr Channel_Type_Enum value = Channel_Type_Enum::UINT8;  };
template <> struct Channel_Type_ID<ChannelType_u12>{ static constexpr Channel_Type_Enum value = Channel_Type_Enum::UINT12; };
template <> struct Channel_Type_ID<ChannelType_u14>{ static constexpr Channel_Type_Enum value = Channel_Type_Enum::UINT14; };
template <> struct Channel_Type_ID<ChannelType_u16>{ static constexpr Channel_Type_Enum value = Channel_Type_Enum::UINT16; };

} // End of tmns::image namespace