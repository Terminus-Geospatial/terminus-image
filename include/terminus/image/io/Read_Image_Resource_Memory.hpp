/**
 * @file    Read_Image_Resource_Memory.hpp
 * @author  Marvin Smith
 * @date    7/13/2023
*/
#pragma once

// Terminus Libraries
#include "../types/Image_Resource_Base.hpp"

// Boost Libraries
#include <boost/utility.hpp>

namespace tmns::image::io {

/**
 * Memory/Driver loading interface
*/
class Read_Image_Resource_Memory : public Read_Image_Resource_Base,
                                          boost::noncopyable
{
    public:

        typedef std::shared_ptr<Read_Image_Resource_Memory> ptr_t;

}; // End of Read_Image_Resource_Memory class

} // end of tmns::image::io namespace