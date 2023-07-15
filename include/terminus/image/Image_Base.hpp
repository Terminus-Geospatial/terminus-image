/**
 * @file    Image.hpp
 * @author  Marvin Smith
 * @date    7/5/2023
*/
#pragma once

// Terminus Libraries
#include "Pixel_Iterator.hpp"

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
        inline ImplT&        impl()       { return static_cast<ImplT&>( *this ); }
        inline ImplT const&  impl() const { return static_cast<ImplT const&>( *this ); }

        /// Returns an iterator pointing to the first pixel in the image.
        iterator begin()             { return       iterator(impl(),0,0,0); }
        const_iterator begin() const { return const_iterator(impl(),0,0,0); }

        /// Returns an iterator pointing one past the last pixel in the image.
        iterator end()             { return       iterator(impl(),0,0,impl().planes()); }
        const_iterator end() const { return const_iterator(impl(),0,0,impl().planes()); }

        /**
         * Get the number of columns in the image.
        */
        virtual size_t cols() const = 0;

        /**
         * Get the number of rows in the image
        */
        virtual size_t rows() const = 0;

        /**
         * Get the number of channels in the image
        */
        virtual size_t channels() const = 0;

        /// Returns an ImageFormat object describing the image format.
        Image_Format format() const
        {
            ImageFormat format( impl().cols(),
                                impl().rows(),
                                impl().planes(),
                                pixel_format(),
                                channel_type(),
                                true );

            return format;
        }

}; // End of ImageBase Class

} // End of tmns::image Namespace
