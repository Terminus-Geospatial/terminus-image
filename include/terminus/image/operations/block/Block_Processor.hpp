/**
 * @file    Block_Processor.hpp
 * @author  Marvin Smith
 * @date    7/23/2023
*/
#pragma once

// Terminus Libraries
#include <terminus/core/work/Thread.hpp>

namespace tmns::image::ops::block {

/**
 * Major block processing routing.  Creates and dispatches all threads
*/
template <typename FuncT>
class Block_Processor
{
    public:

        /**
         * Create a Block_Processor object with the specified parameters.
         * - The function will get executed in "units" of block_size simultaneously
         *   by the specified number of threads.
         * - The func object must have an operator(BBox2i) function that does whatever
        */
        Block_Processor( const FuncT&        func,
                         const math::Size2i& block_size,
                         size_t              threads = std::max( (int)std::thread::hardware_concurrency() / 4, 2 ) )
          : m_func(func),
            m_block_size(block_size),
            m_num_threads( threads ) {}

        /// We will construct and call one BlockThread per thread.
        class Block_Thread
        {
            public:

                // All the BlockThread objects share a reference to a shared Info object,
                // which stores information about what block should be processed next.
                class Info
                {
                    public:

                        Info( const FuncT&         func,
                              const math::Rect2i&  total_bbox,
                              const math::Size2i&  block_size )
                            : m_func(func),
                              m_total_bbox(total_bbox),
                              m_block_bbox( round_down( total_bbox.min().x(),
                                                        block_size.width() ),
                                            round_down( total_bbox.min().y(),
                                                        block_size.height() ),
                                            block_size.width(),
                                            block_size.height() ),
                              m_block_size(block_size) {}


                        // Return the next block bbox to process.
                        math::Rect2i bbox() const
                        {
                            auto block_bbox = math::Rect2i::intersection( m_block_bbox,
                                                                          m_total_bbox );
                            return block_bbox;
                        }

                        // Return the processing function.
                        const FuncT& func() const
                        {
                            return m_func;
                        }

                        // Are we finished?
                        bool complete() const
                        {
                            return ( m_block_bbox.min().y() >= m_total_bbox.max().y() );
                        }

                        // Returns the info mutex, for locking.
                        core::conc::Mutex& mutex()
                        {
                            return m_mutex;
                        }

                        // Advance the block_bbox to point to the next block to process.
                        void advance()
                        {
                            tmns::log::info( "Start of Advance. block_bbox: ", m_block_bbox.to_string(),
                                             ", block_size: ", m_block_size.to_string(),
                                             ", total_bbox: ", m_total_bbox.to_string() );
                            m_block_bbox.min().x() += m_block_size.width();

                            tmns::log::info( "New block bbox: ", m_block_bbox.to_string() );
                            if( m_block_bbox.min().x() >= m_total_bbox.max().x() )
                            {
                                tmns::log::info( "Adjusting" );
                                m_block_bbox.min().x() = round_down( m_total_bbox.min().x(),
                                                                     m_block_size.width() );
                                m_block_bbox.min().y() += m_block_size.height();

                                m_block_bbox.height() = m_block_size.height();
                            }
                            tmns::log::info( "New block bbox: ", m_block_bbox.to_string() );
                            m_block_bbox.width() = m_block_size.width();
                        }

                    private:

                        // This hideous nonsense rounds an integer value *down* to the nearest
                        // multple of the given modulus.  It's this hideous partly because
                        // it avoids modular arithematic on negative numbers, which is technically
                        // implementation-defined in all but the most recent C/C++ standards.
                        static int round_down( int val, int mod)
                        {
                            return val + ((val>=0) ? (-(val%mod)) : (((-val-1)%mod)-mod+1));
                        }

                        const FuncT&       m_func;
                        math::Rect2i       m_total_bbox;
                        math::Rect2i       m_block_bbox;
                        math::Size2i       m_block_size;
                        core::conc::Mutex  m_mutex;
                }; // End class Info

                Block_Thread( Info &info ) : info(info) {}

                void operator()()
                {
                    while( true )
                    {
                        math::Rect2i bbox;
                        {
                            // Grab the next bbox to process, and update it with the
                            // subsequent bbox for the next thread to grab.
                            core::conc::Mutex::Lock lock(info.mutex());
                            if( info.complete() )
                            {
                                return;
                            }
                            bbox = info.bbox();
                            info.advance();
                        }
                        info.func()( bbox );
                    }
                }

            private:

                Info &info;
        }; // End class Block_Thread

        /**
         * Subdivide the bounding-box, then rasterize each in chunks
        */
        void operator()( math::Rect2i bbox ) const
        {
            tmns::log::trace( LOG_IMAGE_TAG(), "start of operator(). bbox: ", bbox.to_string(),
                              ", num_threads: ", m_num_threads,
                              ", block size: ", m_block_size.to_string() );
            typename Block_Thread::Info info( m_func, bbox, m_block_size );

            // Avoid threads altogether in the single-threaded case.
            // Annoyingly, this still creates an unnecessary Mutex.
            if( m_num_threads == 1 )
            {
                Block_Thread bt( info );
                return bt();
            }

            std::vector<std::shared_ptr<Block_Thread> > generators;
            std::vector<std::shared_ptr<core::work::Thread> > threads;

            for( int i = 0; i < m_num_threads; ++i )
            {
                std::shared_ptr<Block_Thread> generator( new Block_Thread( info ) );
                generators.push_back( generator );
                auto thread = std::make_shared<core::work::Thread>( generator );
                threads.push_back( thread );
            }

            for( size_t i = 0; i < m_num_threads; ++i )
            {
                threads[i]->join();
            }
            tmns::log::trace( LOG_IMAGE_TAG(), "end of operator(). bbox: ", bbox.to_string() );
        }

        /**
         * Get this class name
        */
        static std::string class_name()
        {
            return "Block_Processor";
        }

        static std::string full_name()
        {
            return class_name() + "<" + FuncT::full_name() + ">";
        }

    private:

        /// @brief Main worker
        FuncT    m_func;

        /// @brief Block size to process
        math::Size2i m_block_size;

        /// @brief Number of threads to generate
        int   m_num_threads;

}; // End class Block_Processor

} // End of tmns::image::ops::block namespace