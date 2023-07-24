/**
 * @file    Read_Image_Resource_Disk.hpp
 * @author  Marvin Smith
 * @date    7/12/2023
*/
#pragma once

// Terminus Libraries
#include <terminus/core/error/ErrorCategory.hpp>

// Terminus Image Libraries
#include "../types/Image_Resource_Base.hpp"

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
         * Return the filename of the disk image file.
         */
        std::filesystem::path pathname() const;

        /**
         * Print to log-friendly string
        */
        virtual std::string To_Log_String( size_t offset ) const = 0;

    protected:

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
        static bool s_default_rescale;

}; // End of Read_Image_Resource_Disk class


} // end of tmns::image::io namespace