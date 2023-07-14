/**
 * @file    Channel_Types.hpp
 * @author  Marvin Smith
 * @date    7/12/2023
*/
#pragma once

// C++ Libraries
#include <cinttypes>
#include <string>

namespace tmns::image {

template<typename ValueT, int BitDepth>
class Channel_Type
{
    /**
     * Underlying data-type.  For example, 12-bit imagery will get stored in uint16
     * datatypes.
    */
    typedef ValueT data_type;

    /**
     * Datatype to use when storing and adding data.  Note this should be bigger than
     * the underlying type. For example, when storing uint8_t types, accumulate using uin16_t
     * or uint32_t.
    */
    typedef data_type accumulator_type;

    /**
     * Maximum value for this channel type
    */
    static constexpr data_type MAX_VALUE = std::numeric_limits<data_type>::max();

    /**
     * Minimum value for this channel type
    */
    static constexpr data_type MIN_VALUE = std::numeric_limits<data_type>::min();

    /// Number of Bytes
    static constexpr int NUMBER_BYTES = sizeof( data_type );

    /// Bit-Precision of the Pixel Data
    static constexpr int PRECISION = 0;

    static consteval std::string name() { return "Channel_Type<>"; };

}; // End of Channel_Type

/**
 * Channel-Type for UInt8
*/
template<>
class Channel_Type<uint8_t,8>
{
    typedef uint8_t data_type;

    typedef uint16_t accumulator_type;

    static constexpr data_type MAX_VALUE = std::numeric_limits<data_type>::max();

    static constexpr data_type MIN_VALUE = std::numeric_limits<data_type>::min();

    static constexpr int NUMBER_BYTES = sizeof( data_type );

    static constexpr int PRECISION = 0;

    static consteval std::string name() { return "Channel_Type<uint8_t,8>"; };

}; // End of Channel_Type

/**
 * Channel-Type for UInt12
*/
template<>
class Channel_Type<uint16_t,12>
{
    typedef uint16_t data_type;

    typedef uint32_t accumulator_type;

    static constexpr data_type MAX_VALUE = 4095;

    static constexpr data_type MIN_VALUE = 0;

    static constexpr int NUMBER_BYTES = 12;

    static constexpr int PRECISION = 0;

    static consteval std::string name() { return "Channel_Type<uint16_t,12>"; };

}; // End of Channel_Type

/**
 * Channel-Type for UInt14
*/
template<>
class Channel_Type<uint16_t,14>
{
    typedef uint16_t data_type;

    typedef uint32_t accumulator_type;

    static constexpr data_type MAX_VALUE = 16383;

    static constexpr data_type MIN_VALUE = 0;

    static constexpr int NUMBER_BYTES = 14;

    static constexpr int PRECISION = 0;

    static consteval std::string name() { return "Channel_Type<uint16_t,14>"; };

}; // End of Channel_Type

/**
 * Channel-Type for UInt16
*/
template<>
class Channel_Type<uint16_t,16>
{
    typedef uint16_t data_type;

    typedef uint32_t accumulator_type;

    static constexpr data_type MAX_VALUE = std::numeric_limits<data_type>::max();

    static constexpr data_type MIN_VALUE = std::numeric_limits<data_type>::min();

    static constexpr int NUMBER_BYTES = 16;

    static constexpr int PRECISION = 0;

    static consteval std::string name() { return "Channel_Type<uint16_t,16>"; };

}; // End of Channel_Type


// Master List of useful aliases
using ChannelType_u8  = Channel_Type<uint8_t,8>;
using ChannelType_u12 = Channel_Type<uint16_t,12>;
using ChannelType_u14 = Channel_Type<uint16_t,14>;
using ChannelType_u16 = Channel_Type<uint16_t,16>;

} // End of tmns::image namespace