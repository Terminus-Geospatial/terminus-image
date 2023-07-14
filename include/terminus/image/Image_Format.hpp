/**
 * @file    Image_Format.hpp
 * @author  Marvin Smith
 * @date    7/13/2023
*/
#pragma once

/// Terminus Libraries
#include "pixel/Channel_Type_Enum.hpp"
#include "pixel/Pixel_Format_Enum.hpp"

namespace tmns::image {

class Image_Format
{
    public:

        /**
         * Check if the data is fully structured.
        */
        bool complete() const;


    private:

        /// Image Cols
        size_t m_cols { 0 };

        /// Image Rows
        size_t m_rows { 0 };

        /// Channels
        size_t m_channels { 0 };

        /// Pixel Format
        Pixel_Format_Enum m_pixel_type { Pixel_Format_Enum::UNKNOWN };

        /// Channel-Type
        Channel_Type_Enum m_channel_type { Channel_Type_Enum::UNKNOWN };

}; // End of Image_Format Class

} // End of tmns::image namespace