/**
 * @file    Fundamental_Types.hpp
 * @author  Marvin Smith
 * @date    7/23/2023
*/
#pragma once

// C++ Libraries
#include <complex>
#include <type_traits>

namespace tmns::image {

/**
 * Simple structure to verify whether or not a given pixel or channel
 * type is a scalar type.  This "scalar" definition
 *
 * https://en.wikipedia.org/wiki/Scalar_(mathematics)
*/
template <class ValueT> struct Is_Scalar : public std::is_arithmetic<ValueT> {};
template <class ValueT> struct Is_Scalar<std::complex<ValueT> > : public std::true_type {};
template <class ValueT> struct Is_Scalar<const ValueT> : public Is_Scalar<ValueT> {};

/**
 * Returns a type for doing arithmetic on for an input type.  For example, if doing math on
 * an 8-bit unsigned type (uint8_t), it won't take long before it overflows the 8-bits.  Therefore,
 * we should use a 32-bit signed value.  This also allows for subtractions and other operations
 * which may result in negative values.
*/
template <class ValueT> struct Accumulator_Type {};
template <> struct Accumulator_Type<bool>     { typedef int      type; };
template <> struct Accumulator_Type<uint8_t>  { typedef int32_t  type; };
template <> struct Accumulator_Type<int8_t>   { typedef int32_t  type; };
template <> struct Accumulator_Type<uint16_t> { typedef int32_t  type; };
template <> struct Accumulator_Type<int16_t>  { typedef int32_t  type; };
template <> struct Accumulator_Type<uint32_t> { typedef int64_t  type; };
template <> struct Accumulator_Type<int32_t>  { typedef int64_t  type; };
template <> struct Accumulator_Type<uint64_t> { typedef int64_t  type; };
template <> struct Accumulator_Type<int64_t>  { typedef int64_t  type; };
template <> struct Accumulator_Type<float>    { typedef double   type; };
template <> struct Accumulator_Type<double>   { typedef double   type; };
template <class ValueT> struct Accumulator_Type<std::complex<ValueT> >
{
    typedef std::complex<typename Accumulator_Type<ValueT>::type> type;
};

} // End of tmns::image namespace