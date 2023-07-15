/**
 * @file    Image_Resource_Disk_GDAL.hpp
 * @author  Marvin Smith
 * @date    7/14/2023
*/
#pragma once

// Terminus Libraries
#include "../../Read_Image_Resource_Disk.hpp"

namespace tmns::image::io::gdal {

/**
 * @class Read_Image_Resource_Disk_GDAL
 *
 * Disk-Resource loader
*/
class Read_Image_Resource_Disk_GDAL : public Read_Image_Resource_Disk
{
    public:

        /// Parent Pointer Type
        typedef Read_Image_Resource_Disk::ptr_t ParentPtrT;

        /**
         * Destructs the resource in 3 steps
         * 1. Flushes all data in the resource
         * 2. Acquires the global GDAL resource mutex lock
         * 3. Deletes all GDAL references and cleans up.
        */
        virtual ~Read_Image_Resource_Disk_GDAL() override;

        /**
         * Create a new resource and open the image
         *
         * ImageResult will return failure if it's unable to open the image.
        */
        static ImageResult<ParentPtrT> create( const std::filesystem::path& pathname );

        /**
         * Read the image data from disk
        */
        ImageResult<void> read( const Image_Buffer& dest,
                                const math::Rect2i& bbox ) const override
        {
            return outcome::fail( error::ErrorCode::NOT_IMPLEMENTED,
                                  "Not Implemented Yet" );
        }

}; // End of Read_Image_Resource_Disk_GDAL class

} // end of tmns::image::io::gdal namespace