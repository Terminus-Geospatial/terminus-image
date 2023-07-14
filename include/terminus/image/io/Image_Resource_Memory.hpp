/**
 * @file    Image_Resource_Memory.hpp
 * @author  Marvin Smith
 * @date    7/13/2023
*/
#pragma once

// Terminus Libraries
#include "../Image_Resource_Base.hpp"

// Boost Libraries
#include <boost/utility.hpp>

namespace tmns::image::io {

/**
 * Disk/Driver loading interface
*/
class Image_Resource_Memory : public Image_Resource_Base,
                              boost::noncopyable
{

}; // End of Image_Resource_Memory class


} // end of tmns::image::io namespace