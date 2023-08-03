/**
 * @file    Channel_Cast_Utilities.hpp
 * @author  Marvin Smith
 * @date    8/2/2023
*/
#pragma once

// Terminus Libraries
#include "../types/Compound_Types.hpp"
#include "../types/Compound_Utilities.hpp"
#include "../types/Functors.hpp"
#include "../types/compounds/Binary_Compound_Functor.hpp"
#include "../types/compounds/Unary_Compound_Functor.hpp"
#include "Channel_Range.hpp"

// C++ Libraries
#include <numeric>
#include <type_traits>

namespace tmns::image::pix {


/****************************************************/
/*      All Channel_Cast_Functor Class Go Here      */
/****************************************************/

/**
 * Base-type for Channel-Casting.  Does standard (type) casting operator
*/
template <class DestT>
class Channel_Cast_Functor : public Return_Fixed_Type<DestT>
{
    public:

        template <class SourceT>
        DestT operator()( SourceT source ) const
        {
            return (DestT)source;
        }
};

/**
 * Base-type Channel-Cast Functor (w/ rescaling)
*/
template <class DestT>
class Channel_Cast_Rescale_Functor : public Return_Fixed_Type<DestT>
{
    public:

        /**
         * Function operator which interpolates to a new range
        */
        template <class SourceT>
        DestT operator()( SourceT source ) const
        {
            /**
             * Clamping semantics are more reasonable for float->int rescaling.
             * This will not work for clamping and casting to float. For that,
             * Clamp_And_Cast above.
             */
            if( std::is_floating_point<SourceT>::value &&
                ! std::is_floating_point<DestT>::value )
            {
                if( source > Channel_Range<SourceT>::max() )
                {
                    source = Channel_Range<SourceT>::max();
                }
                else if( source < Channel_Range<SourceT>::min() )
                {
                    source = Channel_Range<SourceT>::min();
                }
            }
            return (DestT)(source*(((double)(Channel_Range<DestT>::max()))/(Channel_Range<SourceT>::max())));
        }

        /**
         * No-op if source and dest are same type
        */
        DestT operator()( DestT source ) const
        {
            return source;
        }
};

/**
 * Channel-Cast Functor which does additional Clamping
*/
template <class DestT>
class Channel_Cast_Clamp_Functor : public Return_Fixed_Type<DestT>
{
    public:

        /**
         * Clamp function when types are different
        */
        template <class SourceT>
        DestT operator()( SourceT source ) const
        {
            // Clamp down if over on the max
            if( source > std::numeric_limits<DestT>::max() )
            {
                return std::numeric_limits<DestT>::max();
            }

            // Clamp up if under the min
            else if( source < std::numeric_limits<DestT>::min() )
            {
                return std::numeric_limits<DestT>::min();
            }
            else
            {
                return DestT( source );
            }
        }

        /**
         * Clamp function when the types are the same.
         */
        DestT operator()( DestT source ) const
        {
            return source;
        }
};

/**
 * Channel-Cast functor which rounds
*/
template <class DestT>
class Channel_Cast_Round_Functor : public Return_Fixed_Type<DestT>
{
    public:

        template <class SourceT>
        DestT operator()( SourceT source ) const
        {
            return DestT( std::round( source ) );
        }

        DestT operator()( DestT source ) const
        {
            return source;
        }
};

/**
 * Channel-cast functor with rounding and clamping applied
*/
template <class DestT>
class Channel_Cast_Round_Clamp_Functor : public Return_Fixed_Type<DestT>
{
  public:

        template <class SourceT>
        DestT operator()( SourceT source ) const
        {
            if( source > std::numeric_limits<DestT>::max() )
            {
                return std::numeric_limits<DestT>::max();
            }
            else if( source < std::numeric_limits<DestT>::min() )
            {
                return std::numeric_limits<DestT>::min();
            }
            else
            {
                return DestT( std::round( source ) );
            }
        }

        DestT operator()( DestT source ) const
        {
            return source;
        }
};

/**
 * Method to apply a function on an argument in a typesafe manner
*/
template <typename FunctorT,
          typename ArgT>
typename Compound_Result<FunctorT,ArgT>::type
  compound_apply( const FunctorT& func, const ArgT& arg )
{
    return cmp::Unary_Compound_Functor<FunctorT,ArgT>(func)(arg);
}

/********************************************************************/
/*      All Channel Casting Function Specializations Go Here        */
/********************************************************************/

/**
 * Base instance of channel-cast w/out rescaling
*/
template <class ChannelT, class PixelT>
typename std::enable_if_t< Is_Scalar_Or_Compound<PixelT>::value,
                           typename Compound_Channel_Cast<PixelT, ChannelT>::type >
  channel_cast( PixelT pixel )
{
    return compound_apply( Channel_Cast_Functor<ChannelT>(), pixel );
}

/**
 * Base instance of channel-cast w/ rescaling
*/
template <class ChannelT, class PixelT>
typename std::enable_if_t< Is_Scalar_Or_Compound<PixelT>::value,
                         typename Compound_Channel_Cast<PixelT, ChannelT>::type >
  channel_cast_rescale( PixelT pixel )
{
    return compound_apply( Channel_Cast_Rescale_Functor<ChannelT>(), pixel );
}

/**
 * Channel-Cast operation, without rescaling, which does a clamp
*/
template <class ChannelT, class PixelT>
typename std::enable_if_t< Is_Scalar_Or_Compound<PixelT>::value,
                        typename Compound_Channel_Cast<PixelT, ChannelT>::type >
   channel_cast_clamp( PixelT pixel )
{
    return compound_apply( Channel_Cast_Clamp_Functor<ChannelT>(), pixel );
}

/**
 * Channel-Cast operation with clamping, if integer type
*/
template <class ChannelT, class PixelT>
typename std::enable_if< Is_Scalar_Or_Compound<PixelT>::value,
                         typename Compound_Channel_Cast<PixelT, ChannelT>::type >::type
  channel_cast_clamp_if_int( PixelT pixel )
{
    // if floating point, use normal cast functor, otherwise, clamp
    typedef typename std::conditional<std::is_floating_point<ChannelT>::value,
                                        Channel_Cast_Functor<ChannelT>,
                                        Channel_Cast_Clamp_Functor<ChannelT> >::type FunctorT;
    return compound_apply( FunctorT(), pixel );
}

/**
 * Channel-Cast with rounding
*/
template <class ChannelT, class PixelT>
typename std::enable_if< Is_Scalar_Or_Compound<PixelT>::value,
                         typename Compound_Channel_Cast<PixelT, ChannelT>::type >::type
   channel_cast_round( PixelT pixel )
{
    return compound_apply( Channel_Cast_Round_Functor<ChannelT>(), pixel );
}

/**
 * Channel cast with round for int types
*/
template <class ChannelT, class PixelT>
typename std::enable_if< Is_Scalar_Or_Compound<PixelT>::value,
                         typename Compound_Channel_Cast<PixelT, ChannelT>::type >::type
    channel_cast_round_if_int( PixelT pixel )
{
    typedef typename std::conditional<std::is_floating_point<ChannelT>::value,
                                            Channel_Cast_Functor<ChannelT>,
                                            Channel_Cast_Round_Functor<ChannelT> >::type functor_type;
    return compound_apply( functor_type(), pixel );
}

/**
 * General-Purpose Round and Clamp Functor
*/
template <class ChannelT, class PixelT>
typename std::enable_if< Is_Scalar_Or_Compound<PixelT>::value,
                            typename Compound_Channel_Cast<PixelT, ChannelT>::type >::type
   channel_cast_round_and_clamp( PixelT pixel )
{
    return compound_apply( Channel_Cast_Round_Clamp_Functor<ChannelT>(), pixel );
}

/**
 * Cast the channel by rounding and clamping if input is float and dest is integer
*/
template <class ChannelT, class PixelT>
typename std::enable_if< Is_Scalar_Or_Compound<PixelT>::value,
                                typename Compound_Channel_Cast<PixelT, ChannelT>::type >::type
  channel_cast_round_and_clamp_if_int( PixelT pixel )
{
    // If destination is float, do normal casting, if integer, do the round and clamp functor
    typedef typename std::conditional<std::is_floating_point<ChannelT>::value,
                                            Channel_Cast_Functor<ChannelT>,
                                            Channel_Cast_Round_Clamp_Functor<ChannelT> >::type functor_type;

    // Execute
    return compound_apply( functor_type(), pixel );
}


} // End of tmns::image::pix namespace