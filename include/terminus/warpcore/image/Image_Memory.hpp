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

namespace tmns::warp::image {

template <typename PixelT>
class Image_Memory : public Image_Base<PixelT>
{
    public:


    private:

        /// Pixel Data
        std::shared_ptr<PixelT[]> m_data;


}; // End of Image_Memory Class

template <typename PixelT>
using Image = Image_Memory<PixelT>;

} // End of tmns::warp::image namespace