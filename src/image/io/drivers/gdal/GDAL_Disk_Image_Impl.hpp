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

// Terminus Libraries
#include "../../../error/ErrorCategory.hpp"
#include "../../../pixel/Pixel_Format_Enum.hpp"
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
         * Get the GDALDataset point for whatever dataset is active.
        */
        ImageResult<DatasetPtrT> get_dataset_ptr() const;

        /**
         * Get the image format
        */
        Image_Format format() const;

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


}; // End of GDAL_Disk_Image_Impl class

}