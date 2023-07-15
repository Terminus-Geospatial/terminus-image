/**
 * @file    Memory_Driver_Manager.hpp
 * @author  Marvin Smith
 * @date    7/13/2023
*/
#pragma once

/// External Terminus Libraries
#include <terminus/outcome/Result.hpp>

/// Terminus Libraries
#include "../../error/ErrorCategory.hpp"
#include "../Read_Image_Resource_Memory.hpp"
#include "../Write_Image_Resource_Memory.hpp"
#include "opencv/Read_Image_Resource_Memory_OpenCV.hpp"

// C++ Libraries
#include <deque>
#include <filesystem>
#include <memory>

namespace tmns::image::io {

/**
 * Relatively simple class for storing file input and output drivers.
*/
class Memory_Driver_Manager
{
    public:

        /// Pointer Type
        typedef std::shared_ptr<Memory_Driver_Manager> ptr_t;

        /**
         * Create a Driver-Manager using the default configuration
         *
         * @note The order by which a driver is chosen is the order it is registered.
        */
        static Memory_Driver_Manager::ptr_t create_read_defaults()
        {
            // Create new instance
            auto instance = std::make_shared<Memory_Driver_Manager>();

            // Register each driver
            instance->register_read_driver( std::make_shared<ocv::Read_Image_Resource_Memory_OpenCV>() );

            return instance;
        }

        /**
         * Add a driver to the list
        */
        void register_read_driver( Read_Image_Resource_Memory::ptr_t instance );

        /**
         * Add a driver to the list
        */
        void register_write_driver( Write_Image_Resource_Memory::ptr_t instance );

        /**
         * Select a driver based on the file.
        */
        ImageResult<Read_Image_Resource_Memory::ptr_t> pick_read_driver( const std::filesystem::path& pathname ) const;

        /**
         * Select a driver based on the file.
        */
        ImageResult<Write_Image_Resource_Memory::ptr_t> pick_write_driver( const std::filesystem::path& pathname ) const;

    private:

        /// Default Constructor
        Memory_Driver_Manager() = default;

        /// List of Drivers
        std::deque<Read_Image_Resource_Memory::ptr_t> m_read_drivers;
        std::deque<Write_Image_Resource_Memory::ptr_t> m_write_drivers;

}; // End of Memory_Driver_Manager Class

} // end of tmns::image::io namespace