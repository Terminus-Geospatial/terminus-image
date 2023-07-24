/**
 * @file    Memory_Driver_Manager.hpp
 * @author  Marvin Smith
 * @date    7/13/2023
*/
#pragma once

/// External Terminus Libraries
#include <terminus/core/error/ErrorCategory.hpp>
#include <terminus/outcome/Result.hpp>

/// Terminus Libraries
#include "../Read_Image_Resource_Memory.hpp"
#include "../Write_Image_Resource_Memory.hpp"
#include "opencv/Read_Image_Resource_Memory_OpenCV_Factory.hpp"

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

        /// Type for Read Drivers
        typedef Read_Image_Resource_Memory::ptr_t  ReadDriverT;

        /// Type for Write Drivers
        typedef Write_Image_Resource_Memory::ptr_t WriteDriverT;

        /// Type for Read Driver Factories
        typedef Read_Driver_Factory_Base::ptr_t ReadFactoryT;

        /// Type for Write Driver Factories
        typedef Write_Driver_Factory_Base::ptr_t WriteFactoryT;

        /**
         * Create a Driver-Manager using the default configuration
         *
         * @note The order by which a driver is chosen is the order it is registered.
        */
        static Memory_Driver_Manager::ptr_t create_read_defaults()
        {
            // Create new instance
            auto instance = Memory_Driver_Manager::ptr_t( new Memory_Driver_Manager() );

            // Register each driver
            instance->register_read_driver_factory( std::make_shared<ocv::Read_Image_Resource_Memory_OpenCV_Factory>() );

            return instance;
        }

        /**
         * Add a read driver to the list
        */
        void register_read_driver_factory( ReadFactoryT instance );

        /**
         * Add a write driver to the list
        */
        void register_write_driver_factory( WriteFactoryT instance );

        /**
         * Select a driver based on the file.
        */
        ImageResult<ReadDriverT> pick_read_driver( const std::filesystem::path& pathname ) const;

        /**
         * Select a driver based on the file.
        */
        ImageResult<WriteDriverT> pick_write_driver( const std::filesystem::path& pathname ) const;

    private:

        /// Default Constructor
        Memory_Driver_Manager() = default;

        /// List of Drivers
        std::deque<ReadFactoryT> m_read_driver_factories;
        std::deque<WriteFactoryT> m_write_driver_factories;

}; // End of Memory_Driver_Manager Class

} // end of tmns::image::io namespace