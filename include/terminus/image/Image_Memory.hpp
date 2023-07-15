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
class Image_Memory : public Image_Base<PixelT>
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
         * Get the number of channels in the image
        */
        size_t channels() const override { return m_channels; }

        /**
         * Returns an ImageBuffer describing the image data.
         */
        Image_Buffer buffer() const
        {
            Image_Buffer buffer( data(),
                                 base_type::format() );

            buffer.format  = base_type::format();
            buffer.cstride = sizeof(PixelT);
            buffer.rstride = sizeof(PixelT) * cols();
            buffer.pstride = sizeof(PixelT) * cols() * rows();
            return buffer;
        }

        /**
         * Get a pointer to the top-left corner of the first channel.
        */
        pixel_type* data() const
        {
            return m_data.get();
        }

    private:

        /// Pixel Data
        std::shared_ptr<PixelT[]> m_data;

        /// Image Traits
        size_t m_rows { 0 };
        size_t m_cols { 0 };
        size_t m_channels { 0 };

}; // End of Image_Memory Class

template <typename PixelT>
using Image = Image_Memory<PixelT>;

} // End of tmns::image namespace