/**
 * @file    Image_Disk.hpp
 * @author  Marvin Smith
 * @date    7/20/2023
*/
#pragma once

// Terminus Image Libraries
#include "../io/Read_Image_Resource_Disk.hpp"
#include "Image_Base.hpp"
#include "Image_Resource_Base.hpp"
#include "Image_Resource_View.hpp"

namespace tmns::image {

/**
 * Class for "lazy" evaluation of image data.  Prevents loading too much data into RAM and
 * instead, only "rasterizes" blocks of data when requested.
*/
template <typename PixelT>
class Image_Disk : public Image_Base<Image_Disk<PixelT>>
{
    public:

        /// Pixel Type
        typedef PixelT pixel_type;

        /// Return type when you query actual data
        typedef PixelT& result_type;

        /// Base type of the image
        typedef Image_Base<Image_Disk<PixelT>> base_type;

        /// Image-Type providing block-processing capabilities
        typedef ops::Block_Rasterize_View<Image_Resource_View<PixelT> > impl_type;

        /// Pixel Iterator Type
        typedef typename impl_type::pixel_accessor pixel_accessor;

        /**
         * Destructor
        */
        ~Image_Disk() = default;

        /**
         * Get the number of columns
         */
        size_t cols() const override
        {
            return m_impl.cols();
        }

        /**
         * Get the number of rows.
         */
        size_t rows() const override
        {
            return m_impl.rows();
        }

        /**
         * Get the number of planes
         */
        size_t planes() const override
        {
            return m_impl.planes();
        }

        /**
         * Get the position of the origin
        */
        pixel_accessor origin() const
        {
            return m_impl.origin();
        }

        result_type operator()( size_t x,
                                size_t y,
                                size_t p = 0 ) const
        {
            return m_impl(x,y,p);
        }

        /**
         * Prerasterize the image
        */
        typedef typename impl_type::prerasterize_type prerasterize_type;
        prerasterize_type prerasterize( const math::Rect2i& bbox ) const
        {
            return m_impl.prerasterize( bbox );
        }

        /**
         * Rasterize the image
        */
        template <class DestT>
        void rasterize( const DestT&        dest,
                        const math::Rect2i& bbox ) const
        {
            m_impl.rasterize( dest, bbox );
        }

        std::string pathname() const { return m_resource->pathname(); }

    private:

        // Underlying
        std::shared_ptr<io::Read_Image_Resource_Disk> m_resource;

        /// Underlying block resource
        impl_type m_impl;


}; // End of Image_Disk Class

} // end of tmns::image namespace