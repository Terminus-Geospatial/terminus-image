/**
 * @file    Image_Memory.hpp
 * @author  Marvin Smith
 * @date    7/11/2023
*/
#pragma once

// Terminus Libraries
#include "Image_Base.hpp"

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