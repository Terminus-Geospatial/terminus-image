/**
 * @file    Image_Resource_Disk.hpp
 * @author  Marvin Smith
 * @date    7/12/2023
*/
#pragma once

// Terminus Libraries
#include "../Image_Resource_Base.hpp"

// Boost Libraries
#include <boost/utility.hpp>

// C++ Libraries
#include <memory>

namespace tmns::image::io {

/**
 * Disk/Driver loading interface
*/
class Image_Resource_Disk : public Image_Resource_Base,
                            boost::noncopyable
{
    public:

        /// Pointer Type
        typedef std::shared_ptr<Image_Resource_Disk> ptr_t;


}; // End of Image_Resource_Disk class


} // end of tmns::image::io namespace