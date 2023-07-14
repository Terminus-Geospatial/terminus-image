/**
 * @file    Image_Buffer.hpp
 * @author  Marvin Smith
 * @date    7/13/2023
*/
#pragma once

namespace tmns::image {

/**
 * Represents buffer data in memory.  It stores not only the raw data, but
 * characteristics about it, such as size and types.  It does not allocate
 * data, but merely references it in an organized way.
 */
class Image_Buffer
{
    public:

        /// Underlying data
        void* data;

}; // End of Image_Buffer class

} // End of tmns::image namespace