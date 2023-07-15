/**
 * @file    Write_Image_Resource_Memory.hpp
 * @author  Marvin Smith
 * @date    7/14/2023
*/
#pragma once

namespace tmns::image::io {

/**
 * Memory/Driver loading interface
*/
class Write_Image_Resource_Memory : public Write_Image_Resource_Base,
                                           boost::noncopyable
{
    public:

        /// Pointer Type
        typedef std::shared_ptr<Write_Image_Resource_Memory> ptr_t;

}; // End of Write_Image_Resource_Memory class

} // end of tmns::image::io namespace