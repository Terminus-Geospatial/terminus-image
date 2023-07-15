/**
 * @file    Image_Resource_Base.hpp
 * @author  Marvin Smith
 * @date    7/12/2023
*/
#pragma once

/// External Terminus Libraries
#include <terminus/math/Rectangle.hpp>

/// Terminus Libraries
#include "error/ErrorCategory.hpp"
#include "pixel/Channel_Type_Enum.hpp"
#include "pixel/Pixel_Format_Enum.hpp"
#include "Image_Buffer.hpp"
#include "Image_Format.hpp"

// C++ Libraries
#include <memory>

namespace tmns::image {

class Read_Image_Resource_Base
{
    public:

        typedef std::shared_ptr<Read_Image_Resource_Base> ptr_t;

        virtual ~Read_Image_Resource_Base() = default;

        /**
         * Get the number of columns in the image
        */
        virtual size_t cols() const;

        /**
         * Get the number of rows in the image
        */
        virtual size_t rows() const;

        /**
         * Get the number of channels in the image
        */
        virtual size_t channels() const;

        /**
         * Get the native pixel type for the image resource
        */
        virtual Pixel_Format_Enum pixel_type() const;

        /**
         * Get the underlying channel type for the image
        */
        virtual Channel_Type_Enum channel_type() const;

        /**
         * Get the image format object
        */
        virtual Image_Format format() const = 0;

        /**
         * Read the image data from disk
        */
        virtual ImageResult<void> read( const Image_Buffer& dest,
                                        const math::Rect2i& bbox ) const = 0;

        /*
      /// Does this resource support block reads?
      // If you override this to true, you must implement the other block_read functions
      virtual bool has_block_read() const = 0;

      /// Returns the preferred block size/alignment for partial reads.
      virtual Vector2i block_read_size() const { return Vector2i(cols(),rows()); }

      // Does this resource have a nodata value?
      // If you override this to true, you must implement the other nodata_read functions
      virtual bool has_nodata_read() const = 0;

      /// Fetch this ImageResource's nodata value
      virtual double nodata_read() const {
        vw_throw(NoImplErr() << "This ImageResource does not support nodata_read().");
      }

      /// Return a pointer to the data in the same format as format(). This
      /// might cause a copy, depending on implementation. The shared_ptr will
      /// handle cleanup.
      virtual boost::shared_array<const uint8> native_ptr() const;
      virtual size_t native_size() const;
    */

}; // End of Read_Image_Resource_Base Class

class Write_Image_Resource_Base
{
    public:

        typedef std::shared_ptr<Write_Image_Resource_Base> ptr_t;

        /// @brief  Destructor
        virtual ~Write_Image_Resource_Base() = default;

        virtual ImageResult<void> write( const Image_Buffer& buf,
                                         const math::Rect2i& bbox ) = 0;


}; // End of Write_Image_Resource_Base Class

/**
 * Resource which can load and save an image
*/
class Image_Resource_Base : public Read_Image_Resource_Base,
                                   Write_Image_Resource_Base {};

} // end of tmns::image namespace