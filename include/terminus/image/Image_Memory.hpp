/**
 * @file    Image_Memory.hpp
 * @author  Marvin Smith
 * @date    7/11/2023
*/
#pragma once

// Terminus Libraries
#include "Image_Base.hpp"
#include "Image_Buffer.hpp"

// C++ Libraries
#include <memory>

namespace tmns::image {

template <typename PixelT>
class Image_Memory : public Image_Base<Image_Memory<PixelT>>
{
    public:

        /// Pixel Type
        typedef PixelT pixel_type;

        /// Return type when you query actual data
        typedef PixelT& result_type;

        /// Base type of the image
        typedef Image_Base<Image_Memory<PixelT>> base_type;

        /**
         * Get the number of rows in the image
        */
        size_t rows() const override { return m_rows; }

        /**
         * Get the number of columns in the image
        */
        size_t cols() const override { return m_cols; }

        /**
         * Get the number of planes in the image
        */
        size_t planes() const override { return m_planes; }

        /**
         * Returns an ImageBuffer describing the image data.
         */
        Image_Buffer buffer() const
        {
            Image_Buffer buffer( data(),
                                 base_type::format(),
                                 sizeof(PixelT),
                                 sizeof(PixelT) * cols(),
                                 sizeof(PixelT) * cols() * rows() );
            return buffer;
        }

        /**
         * Get a pointer to the top-left corner of the first channel.
        */
        pixel_type* data() const
        {
            return m_data.get();
        }

        /**
         * Resize the image, allocating new memory if the size has changed.
        */
        ImageResult<void> set_size( size_t cols,
                                    size_t rows,
                                    size_t planes = 1 )
        {
            // Check if already the correct size
            if( cols == m_cols && rows == m_rows && planes == m_planes )
            {
                return outcome::ok();
            }

            /// Hypothetical Max Sizes
            static const size_t MAX_PIXEL_SIZE   = 100000;
            static const size_t MAX_PLANE_COUNT  = 1024;
            static const size_t MAX_TOTAL_PIXELS = 6400000000;

            // Don't oversize
            if( cols >= MAX_PIXEL_SIZE && rows >= MAX_PIXEL_SIZE )
            {
                std::stringstream sout;
                sout << "Will not allocate more than " << MAX_PIXEL_SIZE-1
                     << " pixels on a side.";
                return outcome::fail( error::ErrorCode::OUT_OF_BOUNDS,
                                      sout.str() );
            }
            if( planes >= MAX_PLANE_COUNT )
            {
                std::stringstream sout;
                sout << "Will not allocate more than " << MAX_PLANE_COUNT-1
                     << " planes in the image.";
                return outcome::fail( error::ErrorCode::OUT_OF_BOUNDS,
                                      sout.str() );
            }

            uintmax_t num_pixels = cols * rows * planes;
            if( num_pixels >= MAX_TOTAL_PIXELS )
            {
                std::stringstream sout;
                sout << "Will not allocate more than " << MAX_TOTAL_PIXELS-1
                     << " pixels in the image.";
                return outcome::fail( error::ErrorCode::OUT_OF_BOUNDS,
                                      sout.str() );
            }

            if( num_pixels == 0 )
            {
                m_data.reset();
            }
            else
            {
                // I like this catch because we can wrap the result and not throw
                std::shared_ptr<PixelT> data( new (std::nothrow) PixelT[num_pixels] );

                if( !data )
                {
                    std::stringstream sout;
                    sout << "Cannot allocate enough memory for a " << m_cols << " x "
                         << m_rows << " x " << planes << " image.";
                    return outcome::fail( error::ErrorCode::OUT_OF_MEMORY,
                                          sout.str() );
                }

                m_data = data;
            }
            return outcome::ok();
        }

    private:

        /// Pixel Data
        std::shared_ptr<PixelT[]> m_data;

        /// Image Traits
        size_t m_rows { 0 };
        size_t m_cols { 0 };
        size_t m_planes { 0 };

}; // End of Image_Memory Class

template <typename PixelT>
using Image = Image_Memory<PixelT>;

} // End of tmns::image namespace