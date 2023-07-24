/**
 * @file    Block_Rasterize_View.hpp
 * @author  Marvin Smith
 * @date    7/23/2023
*/
#pragma once

// Terminus Image Libraries
#include "../../pixel/Pixel_Accessor_Loose.hpp"
#include "../../types/Image_Base.hpp"
#include "Block_Generator_Manager.hpp"
#include "Block_Utilities.hpp"

// Terminus Libraries
#include <terminus/core/cache/Cache_Base.hpp>
#include <terminus/math/Size.hpp>

namespace tmns::image::ops {

/**
 * Image type that overloads the rasterize method to allow processing
 * in blocks.  Creates a wrapper around the parent type.
*/
template <typename ImageT>
class Block_Rasterize_View : public Image_Base<Block_Rasterize_View<ImageT>>
{
    public:

        /// Pixel Type
        typedef typename ImageT::pixel_type pixel_type;

        /// Type returned from pixel operators
        typedef typename ImageT::pixel_type result_type;

        /// Pixel Access Type
        typedef Pixel_Accessor_Loose<Block_Rasterize_View> pixel_accessor;

        /**
         * Constructor given an image, block size, thread-count,
         * and optiona cache handle
         */
        Block_Rasterize_View( const ImageT&                   image,
                              const math::Size2i&             block_size,
                              int                             num_threads = 0,
                              core::cache::Cache_Base::ptr_t  cache = nullptr )
          : m_child( new ImageT( image ) ),
            m_block_size( block_size ),
            m_num_threads( num_threads ),
            m_cache_ptr( cache )
        {
            if( m_block_size.width()  <= 0 ||
                m_block_size.height() <= 0 )
            {
                m_block_size = block::get_default_block_size<pixel_type>( image.rows(),
                                                                          image.cols(),
                                                                          image.planes() );
            }

            // Manager is not needed if not using a cache.
            if (m_cache_ptr)
            {
                m_block_manager.initialize( m_cache_ptr,
                                            m_block_size,
                                            m_child );
            }
        }

        /**
         * Number of image columns
         */
        size_t cols() const override
        {
            return m_child->cols();
        }

        /**
         * Number of image rows
         */
        size_t rows() const override
        {
            return m_child->rows();
        }

        /**
         * Number of image planes
         */
        size_t planes() const override
        {
            return m_child->planes();
        }

        /**
         * Get the Child Class
        */
        ImageT*       child()       { return *m_child; }
        const ImageT& child() const { return *m_child; }

        /**
         * Rasterize a single pixel.  Not recommended.
         */
        result_type operator()( size_t x,
                                size_t y,
                                size_t p = 0 ) const
        {
            if ( m_cache_ptr )
            {
                // Note that requesting a value from a handle forces that data to be generated.
                // Early-out optimization for single-block resources
                if( m_block_manager.only_one_block() )
                {
                    const auto& handle = m_block_manager.quick_single_block();
                    result_type result = handle->operator()( x, y, p );
                    handle.release();
                    return result;
                }

                // Otherwise, figure out first what block to fetch
                auto block_index   = m_block_manager.get_block_index( { x, y } );
                const auto& handle = m_block_manager.block( block_index );

                auto start_pixel = m_block_manager.get_block_start_pixel( block_index );

                // Fetch the specific entry from the handle
                result_type result = handle->operator()( x - start_pixel.x(),
                                                         y - start_pixel.y(),
                                                         p );
                handle.release();
                return result;
            } // If we have the cache handle

            // Without a cache, just load the resource directly.  Can be really f-ing slow
            else
            {
                return (*m_child)(x,y,p);
            }
        }

    private:

        /// Child Image.  Necessary to keep local, as the block manager needs it.
        std::shared_ptr<ImageT> m_child;

        /// Block Size (in pixels)
        math::Size2i m_block_size;

        /// Number of threads to use for block processing
        int m_num_threads { 0 };

        /// Cache Handle
        core::cache::Cache_Base::ptr_t m_cache_ptr;

        /// Block-Management API
        block::Block_Generator_Manager<ImageT> m_block_manager;

}; // End of Block_Rasterize_View class

} // End of tmns::image::ops namespace