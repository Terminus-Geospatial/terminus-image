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
    public:

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

        static std::string name() { return "Channel_Type<>"; };

}; // End of Channel_Type

/**
 * Channel-Type for UInt8
*/
template<>
class Channel_Type<uint8_t,8>
{
    public:

        typedef uint8_t data_type;

        typedef int32_t accumulator_type;

        static constexpr data_type MAX_VALUE = std::numeric_limits<data_type>::max();

        static constexpr data_type MIN_VALUE = std::numeric_limits<data_type>::min();

        static constexpr int NUMBER_BYTES = sizeof( data_type );

        static constexpr int PRECISION = 0;

        static std::string name() { return "Channel_Type<uint8_t,8>"; };

}; // End of Channel_Type (UInt8)

/**
 * Channel-Type for Int8
*/
template<>
class Channel_Type<int8_t,8>
{
    public:

        typedef int8_t data_type;

        typedef int32_t accumulator_type;

        static constexpr data_type MAX_VALUE = std::numeric_limits<data_type>::max();

        static constexpr data_type MIN_VALUE = std::numeric_limits<data_type>::min();

        static constexpr int NUMBER_BYTES = sizeof( data_type );

        static constexpr int PRECISION = 0;

        static std::string name() { return "Channel_Type<int8_t,8>"; };

}; // End of Channel_Type (Int8)

/**
 * Channel-Type for UInt12
*/
template<>
class Channel_Type<uint16_t,12>
{
    public:

        typedef uint16_t data_type;

        typedef int32_t accumulator_type;

        static constexpr data_type MAX_VALUE = 4095;

        static constexpr data_type MIN_VALUE = 0;

        static constexpr int NUMBER_BYTES = 12;

        static constexpr int PRECISION = 0;

        static std::string name() { return "Channel_Type<uint16_t,12>"; };

}; // End of Channel_Type

/**
 * Channel-Type for UInt14
*/
template<>
class Channel_Type<uint16_t,14>
{
    public:

        typedef uint16_t data_type;

        typedef int32_t accumulator_type;

        static constexpr data_type MAX_VALUE = 16383;

        static constexpr data_type MIN_VALUE = 0;

        static constexpr int NUMBER_BYTES = 14;

        static constexpr int PRECISION = 0;

        static std::string name() { return "Channel_Type<uint16_t,14>"; };

}; // End of Channel_Type

/**
 * Channel-Type for UInt16
*/
template<>
class Channel_Type<uint16_t,16>
{
    public:

        typedef uint16_t data_type;

        typedef int32_t accumulator_type;

        static constexpr data_type MAX_VALUE = std::numeric_limits<data_type>::max();

        static constexpr data_type MIN_VALUE = std::numeric_limits<data_type>::min();

        static constexpr int NUMBER_BYTES = 16;

        static constexpr int PRECISION = 0;

        static std::string name() { return "Channel_Type<uint16_t,16>"; };

}; // End of Channel_Type (UInt16)

/**
 * Channel-Type for Int16
*/
template<>
class Channel_Type<int16_t,16>
{
    public:

        typedef int16_t data_type;

        typedef int32_t accumulator_type;

        static constexpr data_type MAX_VALUE = std::numeric_limits<data_type>::max();

        static constexpr data_type MIN_VALUE = std::numeric_limits<data_type>::min();

        static constexpr int NUMBER_BYTES = 16;

        static constexpr int PRECISION = 0;

        static std::string name() { return "Channel_Type<int16_t,16>"; };

}; // End of Channel_Type (Int16)

/**
 * Channel-Type for UInt32
*/
template<>
class Channel_Type<uint32_t,32>
{
    public:

        typedef uint32_t data_type;

        typedef int64_t accumulator_type;

        static constexpr data_type MAX_VALUE = std::numeric_limits<data_type>::max();

        static constexpr data_type MIN_VALUE = std::numeric_limits<data_type>::min();

        static constexpr int NUMBER_BYTES = 32;

        static constexpr int PRECISION = 0;

        static std::string name() { return "Channel_Type<uint32_t,32>"; };

}; // End of Channel_Type (UInt32)

/**
 * Channel-Type for Int32
*/
template<>
class Channel_Type<int32_t,32>
{
    public:

        typedef int32_t data_type;

        typedef int64_t accumulator_type;

        static constexpr data_type MAX_VALUE = std::numeric_limits<data_type>::max();

        static constexpr data_type MIN_VALUE = std::numeric_limits<data_type>::min();

        static constexpr int NUMBER_BYTES = 32;

        static constexpr int PRECISION = 0;

        static std::string name() { return "Channel_Type<int32_t,32>"; };

}; // End of Channel_Type (Int32)

/**
 * Channel-Type for UInt64
*/
template<>
class Channel_Type<uint64_t,64>
{
    public:

        typedef uint64_t data_type;

        typedef int64_t accumulator_type;

        static constexpr data_type MAX_VALUE = std::numeric_limits<data_type>::max();

        static constexpr data_type MIN_VALUE = std::numeric_limits<data_type>::min();

        static constexpr int NUMBER_BYTES = 64;

        static constexpr int PRECISION = 0;

        static std::string name() { return "Channel_Type<uint64_t,64>"; };

}; // End of Channel_Type (UInt64)

/**
 * Channel-Type for Int64
*/
template<>
class Channel_Type<int64_t,64>
{
    public:

        typedef int64_t data_type;

        typedef int64_t accumulator_type;

        static constexpr data_type MAX_VALUE = std::numeric_limits<data_type>::max();

        static constexpr data_type MIN_VALUE = std::numeric_limits<data_type>::min();

        static constexpr int NUMBER_BYTES = 64;

        static constexpr int PRECISION = 0;

        static std::string name() { return "Channel_Type<int64_t,64>"; };

}; // End of Channel_Type (Int64)

/**
 * Channel-Type for Float32
*/
template<>
class Channel_Type<float,1>
{
    public:

        typedef float data_type;

        typedef double accumulator_type;

        static constexpr data_type MAX_VALUE = 1;

        static constexpr data_type MIN_VALUE = 0;

        static constexpr int NUMBER_BYTES = 4;

        static constexpr int PRECISION = 32;

        static std::string name() { return "Channel_Type<float,1>"; };

}; // End of Channel_Type

/**
 * Channel-Type for Float32Free
*/
template<>
class Channel_Type<float,2>
{
    public:

        typedef float data_type;

        typedef double accumulator_type;

        static constexpr data_type MAX_VALUE = 1;

        static constexpr data_type MIN_VALUE = -1;

        static constexpr int NUMBER_BYTES = 4;

        static constexpr int PRECISION = 32;

        static std::string name() { return "Channel_Type<float,2>"; };

}; // End of Channel_Type

/**
 * Channel-Type for Float64
*/
template<>
class Channel_Type<double,1>
{
    public:

        typedef double data_type;

        typedef double accumulator_type;

        static constexpr data_type MAX_VALUE = 1;

        static constexpr data_type MIN_VALUE = 0;

        static constexpr int NUMBER_BYTES = 8;

        static constexpr int PRECISION = 64;

        static std::string name() { return "Channel_Type<double,1>"; };

}; // End of Channel_Type

/**
 * Channel-Type for Float64
*/
template<>
class Channel_Type<double,2>
{
    public:

        typedef double data_type;

        typedef double accumulator_type;

        static constexpr data_type MAX_VALUE = 1;

        static constexpr data_type MIN_VALUE = -1;

        static constexpr int NUMBER_BYTES = 8;

        static constexpr int PRECISION = 64;

        static std::string name() { return "Channel_Type<double,2>"; };

}; // End of Channel_Type


// Master List of useful aliases
using ChannelType_u8   = Channel_Type<uint8_t,8>;
using ChannelType_u12  = Channel_Type<uint16_t,12>;
using ChannelType_u14  = Channel_Type<uint16_t,14>;
using ChannelType_u16  = Channel_Type<uint16_t,16>;
using ChannelType_u32  = Channel_Type<uint32_t,32>;
using ChannelType_u64  = Channel_Type<uint64_t,64>;

using ChannelType_i8   = Channel_Type<int8_t,8>;
using ChannelType_i16  = Channel_Type<int16_t,16>;
using ChannelType_i32  = Channel_Type<int32_t,32>;
using ChannelType_i64  = Channel_Type<int64_t,64>;

using ChannelType_f32  = Channel_Type<float,1>;
using ChannelType_f32f = Channel_Type<float,2>;
using ChannelType_f64  = Channel_Type<double,1>;
using ChannelType_f64f = Channel_Type<double,2>;

} // End of tmns::image namespace