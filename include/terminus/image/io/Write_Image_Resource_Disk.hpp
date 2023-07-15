/**
 * @file    Write_Image_Resource_Disk.hpp
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
class Write_Image_Resource_Disk : public Write_Image_Resource_Base,
                                         boost::noncopyable
{
    public:

        /// Pointer Type
        typedef std::shared_ptr<Write_Image_Resource_Disk> ptr_t;


}; // End of Write_Image_Resource_Disk class

} // end of tmns::image::io namespace