/**
 * @file    Read_Image_Resource_Disk_GDAL.hpp
 * @author  Marvin Smith
 * @date    7/14/2023
*/
#pragma once

// Terminus Libraries
#include "../../Read_Image_Resource_Disk.hpp"
#include "GDAL_Codes.hpp"

// C++ Libraries
#include <tuple>
#include <vector>

namespace tmns::image::io::gdal {

class GDAL_Disk_Image_Impl;

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

        /// Lookup Table for mapping GDAL Code Codes to Terminus Pixel-Types
        typedef std::vector<std::tuple<std::vector<int>,Pixel_Format_Enum>> ColorCodeLookupT;

        /**
         * Parameterized Constructor
         * @param pathname Image to open
        */
        Read_Image_Resource_Disk_GDAL( const std::filesystem::path& pathname,
                                       const ColorCodeLookupT&      color_reference_lut = Use_Default_Color_LUT() );

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
         * Open the dataset
        */
        ImageResult<void> open( const std::filesystem::path& pathname );

        /**
         * Read the image data from disk
        */
        ImageResult<void> read( const Image_Buffer& dest,
                                const math::Rect2i& bbox ) const override
        {
            return outcome::fail( error::ErrorCode::NOT_IMPLEMENTED,
                                  "Not Implemented Yet" );
        }

        /**
         * Default mapping of Color-Codes in GDAL to Pixel-Types
        */
        inline static ColorCodeLookupT Use_Default_Color_LUT()
        {
            ColorCodeLookupT lut;

            // Grayscale
            lut.push_back( std::make_tuple( std::vector<int>{ static_cast<int>(GDAL_Color_Codes::GCI_GrayIndex) },
                                            Pixel_Format_Enum::GRAY ) );

            // Grayscale with alpha
            lut.push_back( std::make_tuple( std::vector<int>{ static_cast<int>(GDAL_Color_Codes::GCI_GrayIndex),
                                                              static_cast<int>(GDAL_Color_Codes::GCI_AlphaBand) },
                                            Pixel_Format_Enum::GRAY ) );

            // RGB
            lut.push_back( std::make_tuple( std::vector<int>{ static_cast<int>(GDAL_Color_Codes::GCI_RedBand),
                                                              static_cast<int>(GDAL_Color_Codes::GCI_GreenBand),
                                                              static_cast<int>(GDAL_Color_Codes::GCI_BlueBand) },
                                            Pixel_Format_Enum::RGB ) );

            // RGBA
            lut.push_back( std::make_tuple( std::vector<int>{ static_cast<int>(GDAL_Color_Codes::GCI_RedBand),
                                                              static_cast<int>(GDAL_Color_Codes::GCI_GreenBand),
                                                              static_cast<int>(GDAL_Color_Codes::GCI_BlueBand),
                                                              static_cast<int>(GDAL_Color_Codes::GCI_AlphaBand) },
                                            Pixel_Format_Enum::RGBA ) );

            return lut;
        }

    private:

        std::shared_ptr<GDAL_Disk_Image_Impl> m_impl;

        /// Color Code Lookup Table
        ColorCodeLookupT m_color_reference_lut;

}; // End of Read_Image_Resource_Disk_GDAL class

} // end of tmns::image::io::gdal namespace