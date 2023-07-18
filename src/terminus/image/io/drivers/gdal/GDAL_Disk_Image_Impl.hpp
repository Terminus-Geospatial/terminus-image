/**
 * @file    GDAL_Disk_Image_Impl.hpp
 * @author  Marvin Smith
 * @date    7/15/2023
*/
#pragma once

// GDAL Libraries
#include <gdal.h>
#include <gdal_priv.h>

// C++ Libraries
#include <filesystem>
#include <tuple>
#include <vector>

// External Terminus Libraries
#include <terminus/math/Rectangle.hpp>
#include <terminus/math/Vector.hpp>

// Terminus Libraries
#include "../../../error/ErrorCategory.hpp"
#include "../../../pixel/Pixel_Format_Enum.hpp"
#include "../../../pixel/Pixel_RGBA.hpp"
#include "../../../Image_Buffer.hpp"
#include "../../../Image_Format.hpp"

namespace tmns::image::io::gdal {

class GDAL_Disk_Image_Impl
{
    public:

        typedef std::shared_ptr<GDALDataset> DatasetPtrT;

        typedef std::vector<std::tuple<std::vector<int>,Pixel_Format_Enum>> ColorCodeLookupT;

        /**
         * Constructor
        */
        GDAL_Disk_Image_Impl( const std::filesystem::path& pathname,
                              const ColorCodeLookupT&      color_reference_lut );

        /**
         * Open the dataset
        */
        ImageResult<void> open( const std::filesystem::path& pathname );

        /**
         * Read the raster from disk
        */
        ImageResult<void> read( const Image_Buffer&         dest,
                                const math::Rectangle<int>& bbox,
                                bool                        rescale ) const;

        /**
         * Print to log-friendly string
        */
        std::string To_Log_String( size_t offset ) const;

        /**
         * Get the image format
        */
        Image_Format format() const;
        
        /**
         * Get the GDALDataset point for whatever dataset is active.
        */
        ImageResult<DatasetPtrT> get_dataset_ptr() const;

        /**
         * Get the default block size
        */
        math::Vector2i default_block_size() const;

        /**
         * Check if driver type is trusted to report valid single-line block sizes
        */
        static bool blocksize_whitelist( const GDALDriver* driver );

    private:

        /// Pathname to image
        std::filesystem::path m_pathname;

        /// GDAL Datasets
        std::shared_ptr<GDALDataset> m_read_dataset;
        std::shared_ptr<GDALDataset> m_write_dataset;

        /// Format Information
        Image_Format m_format;

        /// Color Code -> PixelType lookup table
        ColorCodeLookupT m_color_reference_lut;

        /// Block Size Information
        math::Vector2i m_blocksize;

        /// Image Palette
        std::vector<PixelRGBA_u8> m_color_table;

}; // End of GDAL_Disk_Image_Impl class

}