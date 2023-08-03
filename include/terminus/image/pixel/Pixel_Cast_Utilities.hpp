/**
 * @file    Pixel_Cast_Utilities.hpp
 * @author  Marvin Smith
 * @date    8/2/2023
*/
#pragma once

// Terminus Libraries
#include "../types/Functors.hpp"
#include "Channel_Cast_Utilities.hpp"

namespace tmns::image::pix {

/************************************************************/
/*          All Pixel_Cast_Helper Classes Go Here           */
/************************************************************/

/**
 * No-Op cast helper.  Useful for when types are already the same.
*/
template <bool SameN, bool SrcN, bool RescaleN>
struct Pixel_Cast_Helper
{
    template <class DestT, class SrcT>
    static DestT convert( SrcT src )
    {
        return DestT( src );
    }
};

/********************************************************************/
/*          Pixel Casting Functions (w/ and w/out rescale)          */
/********************************************************************/

/**
 * Function for doing a no-op when types are the same
*/
template <typename DestT,
          typename SourceT>
typename std::enable_if_t<Is_Scalar_Or_Compound<SourceT>::value, DestT>
    pixel_cast( SourceT src )
{
    // Get the source channel type
    typedef typename Compound_Channel_Type<SourceT>::type SourceChannelT;

    // Destination channel type
    typedef typename Compound_Channel_Type<DestT>::type   DestChannelT;

    // Check if they are the same
    typedef typename std::is_same<SourceChannelT,DestChannelT>::type IsSameT;

    /// Pixel the Pixel_Cast_Helper class
    typedef Pixel_Cast_Helper< IsSameT::value, (sizeof(SourceChannelT) > sizeof(DestChannelT) ),false> helper;

    // Do the conversion
    return helper::template convert<DestChannelT>( src );
}

/**
 * Function for a no-op pixel-cast without scaling.
*/
template <typename DestT,
          typename SourceT>
typename std::enable_if_t< Is_Scalar_Or_Compound<SourceT>::value, DestT >
   pixel_cast_rescale( SourceT src )
{
    // Get source and destination channel types
    typedef typename Compound_Channel_Type<SourceT>::type SourceChannelT;
    typedef typename Compound_Channel_Type<DestT>::type   DestChannelT;

    // Check if pixel types are the same
    typedef typename std::is_same<SourceChannelT,DestChannelT>::type IsSameT;
    typedef Pixel_Cast_Helper< IsSameT::value,
                                ( sizeof(SourceChannelT) > sizeof(DestChannelT)),
                                 true > helper;
    return helper::template convert<DestT>( src );
}

/**
 * Pixel cast helper class without rescaling if precision is less or the same
 *
 * Executes a channel-cast in-sync
*/
template <>
struct Pixel_Cast_Helper<false, false, false>
{
    template <class DestT, class SrcT>
    static DestT convert( SrcT src )
    {
        typedef typename Compound_Channel_Type<DestT>::type DestChannelT;
        return pixel_cast<DestT>( channel_cast<DestChannelT>( src ) );
    }
};

/**
 * Pixel cast helper class without rescaling if precision is greater
*/
template <>
struct Pixel_Cast_Helper<false, true, false>
{
    template <class DestT, class SrcT>
    static DestT convert( SrcT src )
    {
        // Get the source and destination types
        typedef typename Compound_Channel_Type<SrcT>::type  SourceChannelT;
        typedef typename Compound_Channel_Type<DestT>::type DestChannelT;

        // Setup destination pixel-type
        typedef typename Compound_Channel_Cast<DestT,SourceChannelT>::type DestPixelT;

        // Execute a channel cast
        return channel_cast<DestChannelT>( pixel_cast<DestPixelT>( src ) );
    }
  };

/**
 * Pixel Cast w/ rescaling when Source has less or same precision as destination
*/
template <>
struct Pixel_Cast_Helper<false, false, true>
{
    template <class DestT, class SrcT>
    static DestT convert( SrcT src )
    {
        // Determine destination channel-type
        typedef typename Compound_Channel_Type<DestT>::type DestChannelT;

        // Cast the pixel after a channel-cast (with-rescale)
        return pixel_cast<DestT>( channel_cast_rescale<DestChannelT>( src ) );
    }
};

/**
 * Pixel cast w/ rescale when Source has greater precision than destination
*/
template <>
struct Pixel_Cast_Helper<false, true, true>
{
    template <class DestT, class SrcT>
    static DestT convert( SrcT src )
    {
        // Figure out source and destination channel-types
        typedef typename Compound_Channel_Type<SrcT>::type SourceChannelT;
        typedef typename Compound_Channel_Type<DestT>::type DestChannelT;

        // Solve destination pixel-type
        typedef typename Compound_Channel_Cast<DestT,SourceChannelT>::type DestPixelT;

        // Perform pixel cast, followed by channel-cast
        return channel_cast_rescale<DestChannelT>( pixel_cast<DestPixelT>( src ) );
    }
};


/************************************************/
/*          Pixel Cast Function Objects         */
/************************************************/

/**
 * Function object designed to convert pixel types
*/
template <typename PixelT>
struct Pixel_Cast_Functor : private Return_Fixed_Type<PixelT>
{
    /**
     * Cast the pixel
    */
   template <typename ArgumentT>
   PixelT operator()( ArgumentT pixel ) const
   {
        return pixel_cast<PixelT>( pixel );
   }

}; // End of Pixel_Cast_Functor

/**
 * Function Object designed to convert pixel-types with proper channel
 * rescaling
*/
template <typename PixelT>
struct Pixel_Cast_Rescale_Functor : private Return_Fixed_Type<PixelT>
{
    public:

        template <typename ArgumentT>
        PixelT operator()( ArgumentT pixel ) const
        {
            return pixel_cast_rescale<PixelT>( pixel );
        }
}; // End of Pixel_Cast_Rescale_Functor

} // End of tmns::image::pix namespace