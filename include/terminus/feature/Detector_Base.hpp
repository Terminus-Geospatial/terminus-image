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
         * Function / Call Operator
        */
        template <typename PixelT>
        ImageResult<Interest_Point_List> operator()( const image::Image_Memory<PixelT>&  image,
                                                     size_t                              max_features )
        {
            {
                std::unique_lock<std::mutex> lck( m_log_mtx );
                std::stringstream sout;
                sout << "Computing interest points for region " << image.cols() << " x " << image.rows();
            }

            // Rasterize
            image::Image_Memory<PixelT> dest_image;
            auto res = image.impl().rasterize( image.full_bbox(), dest_image );
        }

        /**
         * Function / Call Operator
        */
        template <typename ImageT>
        ImageResult<Interest_Point_List> operator()( const image::Image_Base<ImageT>&  image,
                                                     size_t                            max_features )
        {
            {
                std::unique_lock<std::mutex> lck( m_log_mtx );
                std::stringstream sout;
                sout << "Computing interest points for region " << image.cols() << " x " << image.rows();
                m_logger.trace( sout.str() );
            }

            // Rasterize
            image::Image_Memory<typename ImageT::pixel_type> dest_image;
            auto res = image.impl().rasterize( image.full_bbox(), dest_image );
            return this->operator()( dest_image, max_features );
        }

        /**
         * Get the class name
         */
        virtual std::string class_name() const = 0;

    private:

        /// Internal Configuration Options
        Detector_Config_Base::ptr_t m_config;

        /// Detector Logger Instance
        tmns::log::Logger m_logger;

        /// Logger Mutex
        std::mutex m_log_mtx;

}; // End of Detector_Base class

} // End of tmns::feature namespace