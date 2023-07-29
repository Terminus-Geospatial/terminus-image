/**
 * @file    Image.hpp
 * @author  Marvin Smith
 * @date    7/5/2023
*/
#pragma once

// Terminus Image Libraries
#include "../pixel/Channel_Type_ID.hpp"
#include "../pixel/Pixel_Format_ID.hpp"
#include "Image_Format.hpp"
#include "Pixel_Iterator.hpp"

// Terminus Libraries
#include <terminus/math/Rectangle.hpp>

namespace tmns::image {

/**
 * @class Image_Base
 *
 * Base image type.  This is important cause we want either lazy or eager
 * models.  This will be the key base class keeping them tied together.  Please be
 * very careful when touching this class.
 *
 * This class uses Curiously-Recurring Template Pattern.
*/
template <typename ImplT>
class Image_Base
{
    public:

        /// @brief An STL-compatible iterator type.
        typedef Pixel_Iterator<      ImplT> iterator;

        /// @brief  An STL-compatible const-iterator type
        typedef Pixel_Iterator<const ImplT> const_iterator;


        /// Methods to access the derived type when sitting in the base
        ImplT&        impl()       { return static_cast<ImplT&>( *this ); }
        ImplT const&  impl() const { return static_cast<ImplT const&>( *this ); }

        /// Returns an iterator pointing to the first pixel in the image.
        iterator begin()             { return       iterator(impl(),0,0,0); }
        const_iterator begin() const { return const_iterator(impl(),0,0,0); }

        /// Returns an iterator pointing one past the last pixel in the image.
        iterator end()             { return       iterator(impl(),0,0,impl().planes()); }
        const_iterator end() const { return const_iterator(impl(),0,0,impl().planes()); }

        /**
         * Get the number of columns in the image.
        */
        size_t cols() const
        {
            return impl().cols();
        }

        /**
         * Get the number of rows in the image
        */
        size_t rows() const
        {
            return impl().rows();
        }

        /**
         * Get the number of channels in the image
        */
        size_t channels() const
        {
            return ImplT::pixel_type::NUM_CHANNELS;
        };

        /**
         * Get the number of planes in the image
        */
        size_t planes() const
        {
            return impl().planes();
        }

        /**
         * Create a Bounding Box for the full image dimensions.  Nice
         * helper script for APIs that need math::Rect2i inputs.
        */
        virtual math::Rect2i full_bbox() const
        {
            return math::Rect2i( 0, 0, cols(), rows() );
        }

        /**
         * Get the Pixel-Format Enum from the Pixel-Type
        */
        Pixel_Format_Enum pixel_format() const
        {
            return Pixel_Format_ID<typename ImplT::pixel_type>::value;
        }

        /**
         * Get the channel-type from the image's pixel type
        */
        Channel_Type_Enum channel_type() const
        {
            typedef typename ImplT::pixel_type ptype;
            return Channel_Type_ID<typename ptype::channel_type>::value;
        }


        /// Returns an ImageFormat object describing the image format.
        Image_Format format() const
        {
            Image_Format format( impl().cols(),
                                 impl().rows(),
                                 impl().planes(),
                                 pixel_format(),
                                 channel_type(),
                                 true );

            return format;
        }

    protected:

        /// The user can't be allowed to use these
        Image_Base() = default;

        Image_Base( const Image_Base& rhs ) = default;

        Image_Base& operator = ( const Image_Base& rhs )
        {
            return (*this);
        }

}; // End of ImageBase Class

} // End of tmns::image Namespace
