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

// Unsigned Integer Types
template <> struct Channel_Type_ID<ChannelType_u8>{  static constexpr Channel_Type_Enum value = Channel_Type_Enum::UINT8;  };
template <> struct Channel_Type_ID<ChannelType_u12>{ static constexpr Channel_Type_Enum value = Channel_Type_Enum::UINT12; };
template <> struct Channel_Type_ID<ChannelType_u14>{ static constexpr Channel_Type_Enum value = Channel_Type_Enum::UINT14; };
template <> struct Channel_Type_ID<ChannelType_u16>{ static constexpr Channel_Type_Enum value = Channel_Type_Enum::UINT16; };
template <> struct Channel_Type_ID<ChannelType_u32>{ static constexpr Channel_Type_Enum value = Channel_Type_Enum::UINT32; };
template <> struct Channel_Type_ID<ChannelType_u64>{ static constexpr Channel_Type_Enum value = Channel_Type_Enum::UINT64; };

// Signed Integer Types
template <> struct Channel_Type_ID<ChannelType_i8>{  static constexpr Channel_Type_Enum value = Channel_Type_Enum::INT8;  };
template <> struct Channel_Type_ID<ChannelType_i16>{ static constexpr Channel_Type_Enum value = Channel_Type_Enum::INT16;  };
template <> struct Channel_Type_ID<ChannelType_i32>{ static constexpr Channel_Type_Enum value = Channel_Type_Enum::INT32;  };
template <> struct Channel_Type_ID<ChannelType_i64>{ static constexpr Channel_Type_Enum value = Channel_Type_Enum::INT64;  };

// Floating-Point Types
template <> struct Channel_Type_ID<ChannelType_f32>{ static constexpr Channel_Type_Enum value = Channel_Type_Enum::FLOAT32;  };
template <> struct Channel_Type_ID<ChannelType_f64>{ static constexpr Channel_Type_Enum value = Channel_Type_Enum::FLOAT64;  };

// Basic Types
template<> struct Channel_Type_ID<uint8_t>     { static const Channel_Type_Enum value = Channel_Type_Enum::UINT8; };
template<> struct Channel_Type_ID<int16_t>     { static const Channel_Type_Enum value = Channel_Type_Enum::INT16; };
template<> struct Channel_Type_ID<uint16_t>    { static const Channel_Type_Enum value = Channel_Type_Enum::UINT16; };
template<> struct Channel_Type_ID<int32_t>     { static const Channel_Type_Enum value = Channel_Type_Enum::INT32; };
template<> struct Channel_Type_ID<uint32_t>    { static const Channel_Type_Enum value = Channel_Type_Enum::UINT32; };
template<> struct Channel_Type_ID<int64_t>     { static const Channel_Type_Enum value = Channel_Type_Enum::INT64; };
template<> struct Channel_Type_ID<uint64_t>    { static const Channel_Type_Enum value = Channel_Type_Enum::UINT64; };
template<> struct Channel_Type_ID<float>       { static const Channel_Type_Enum value = Channel_Type_Enum::FLOAT32; };
template<> struct Channel_Type_ID<double>      { static const Channel_Type_Enum value = Channel_Type_Enum::FLOAT64; };

} // End of tmns::image namespace