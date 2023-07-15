/**
 * @file    Read_Image_Resource_Disk_GDAL_Factory.hpp
 * @author  Marvin Smith
 * @date    7/14/2023
*/
#pragma once

/// Terminus Libraries
#include "../Read_Driver_Factory_Base.hpp"
#include "Read_Image_Resource_Disk_GDAL.hpp"

namespace tmns::image::io::gdal {

/**
 * Exists purely to crank out GDAL Read-Resources.
*/
class Read_Image_Resource_Disk_GDAL_Factory : public Read_Driver_Factory_Base
{
    public:

        /// Disk Driver Pointer Type
        typedef Read_Image_Resource_Base::ptr_t DriverT;

        Read_Image_Resource_Disk_GDAL_Factory() = default;

        ~Read_Image_Resource_Disk_GDAL_Factory() override = default;

        /**
         * Check if image type is supported by the GDAL driver
        */
        bool is_image_supported( const std::filesystem::path& pathname ) const override;

        /**
         * Create the GDAL Image Disk-Reader Resource
        */
        ImageResult<DriverT> create( const std::filesystem::path& pathname ) const override;

    private:

        /// List of supported extensions
        std::vector<std::string> m_supported_extensions { ".tif", ".png", ".jpg", ".ntf" };

}; // end of Read_Image_Resource_Disk_GDAL_Factory

} // end of tmns::image::io::gdal namespace