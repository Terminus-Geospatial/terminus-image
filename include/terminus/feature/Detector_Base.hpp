/**
 * @file    Detector_Base.hpp
 * @author  Marvin Smith
 * @date    7/30/2023
*/
#pragma once

// Terminus Libraries
#include <terminus/core/error/ErrorCategory.hpp>
#include <terminus/log/Logger.hpp>

// Terminus Feature Libraries
#include "../image/types/Image_Base.hpp"
#include "../image/types/Image_Memory.hpp"
#include "Detector_Config_Base.hpp"
#include "Interest_Point.hpp"

// C++ Libraries
#include <memory>
#include <mutex>

namespace tmns::feature {

/**
 * Base class for all feature point detection modules.
*/
class Detector_Base
{
    public:

        /// Pointer Type
        typedef std::shared_ptr<Detector_Base> ptr_t;

        /**
         * Constructor given a configuration.  Null configuration will be bad,
         * so always provide a valid and usable configuration.
        */
        Detector_Base( Detector_Config_Base::ptr_t config );

        /**
         * Destructor
        */
        virtual ~Detector_Base() = default;

        /**
         * Function / Call Operator
        */
        template <typename PixelT>
        ImageResult<Interest_Point_List> operator()( const image::Image_Memory<PixelT>&  image,
                                                     bool                                cast_if_ptype_unsupported = true )
        {
            {
                std::unique_lock<std::mutex> lck( m_log_mtx );
                std::stringstream sout;
                sout << "Computing interest points for region " << image.cols() << " x " << image.rows();
            }

            // Rasterize
            return this->process_image( image.buffer(),
                                        cast_if_ptype_unsupported );
        }

        /**
         * Function / Call Operator
        */
        template <typename ImageT>
        ImageResult<Interest_Point_List> operator()( const image::Image_Base<ImageT>&  image,
                                                     bool                              cast_if_ctype_unsupported = true )
        {
            {
                std::unique_lock<std::mutex> lck( m_log_mtx );
                std::stringstream sout;
                sout << "Computing interest points for region " << image.cols() << " x " << image.rows();
                m_logger.trace( sout.str() );
            }

            // Rasterize to a memory image
            image::Image_Memory<typename ImageT::pixel_type> dest_image;
            auto res = image.impl().rasterize( image.full_bbox(), dest_image );
            return this->operator()( dest_image,
                                     cast_if_ctype_unsupported );
        }

        /**
         * Process the image and detect keypoints
         */
        virtual ImageResult<Interest_Point_List> process_image( const image::Image_Buffer& image_data,
                                                                bool                       cast_if_ctype_unsupported ) = 0;

        /**
         * Get the class name
         */
        virtual std::string class_name() const = 0;

    protected: 

        /// Detector Logger Instance
        tmns::log::Logger m_logger;

        /// Logger Mutex
        std::mutex m_log_mtx;
        
    private:

        /// Internal Configuration Options
        Detector_Config_Base::ptr_t m_config;

}; // End of Detector_Base class

} // End of tmns::feature namespace