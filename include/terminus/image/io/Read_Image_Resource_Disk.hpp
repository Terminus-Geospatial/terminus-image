/**
 * @file    Read_Image_Resource_Disk.hpp
 * @author  Marvin Smith
 * @date    7/12/2023
*/
#pragma once

// Terminus Libraries
#include "../error/ErrorCategory.hpp"
#include "../Image_Resource_Base.hpp"

// Boost Libraries
#include <boost/utility.hpp>

// C++ Libraries
#include <filesystem>
#include <memory>

namespace tmns::image::io {

/**
 * Disk/Driver loading interface
*/
class Read_Image_Resource_Disk : public Read_Image_Resource_Base,
                                        boost::noncopyable
{
    public:

        /// Pointer Type
        typedef std::shared_ptr<Read_Image_Resource_Disk> ptr_t;

        ~Read_Image_Resource_Disk() override = default;

        /**
         * Get the image format of data on disk.
        */
        virtual Image_Format format() const override;

        /// Return the filename of the disk image file.
        std::filesystem::path pathname() const;

    private:

        /**
         * Constructor
         * @param pathname Image to load.
        */
        Read_Image_Resource_Disk( const std::filesystem::path& pathname );

        /// Image Buffer Information
        Image_Format m_format;

        /// Pathname
        std::filesystem::path m_pathname;

        /// Flag to control if we rescale values during channel/pixel conversions.
        bool        m_rescale;

        /// Flag for default behavior [Initialized to true]
        static bool default_rescale;

}; // End of Read_Image_Resource_Disk class


} // end of tmns::image::io namespace