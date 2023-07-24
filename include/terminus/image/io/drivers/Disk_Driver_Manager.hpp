/**
 * @file    Disk_Driver_Manager.hpp
 * @author  Marvin Smith
 * @date    7/13/2023
*/
#pragma once

/// Terminus Libraries
#include <terminus/core/error/ErrorCategory.hpp>

/// Terminus Image Libraries
#include "../Read_Image_Resource_Disk.hpp"
#include "../Write_Image_Resource_Disk.hpp"
#include "gdal/Read_Image_Resource_Disk_GDAL_Factory.hpp"
#include "Read_Driver_Factory_Base.hpp"
#include "Write_Driver_Factory_Base.hpp"

// C++ Libraries
#include <deque>
#include <memory>

namespace tmns::image::io {

/**
 * Relatively simple class for storing file input and output drivers.
*/
class Disk_Driver_Manager : boost::noncopyable
{
    public:

        /// Pointer Type
        typedef std::shared_ptr<Disk_Driver_Manager> ptr_t;

        /// Type for Read Drivers
        typedef Read_Image_Resource_Disk::ptr_t  ReadDriverT;

        /// Type for Write Drivers
        typedef Write_Image_Resource_Disk::ptr_t WriteDriverT;

        /// Type for Read Driver Factories
        typedef Read_Driver_Factory_Base::ptr_t ReadFactoryT;

        /// Type for Write Driver Factories
        typedef Write_Driver_Factory_Base::ptr_t WriteFactoryT;

        /**
         * Create a Driver-Manager using the default configuration
         *
         * @note The order by which a driver is chosen is the order it is registered.
        */
        static Disk_Driver_Manager::ptr_t create_read_defaults()
        {
            // Create new instance
            auto instance = Disk_Driver_Manager::ptr_t( new Disk_Driver_Manager() );

            // Register each driver
            instance->register_read_driver_factory( std::make_shared<gdal::Read_Image_Resource_Disk_GDAL_Factory>() );

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
        Disk_Driver_Manager() = default;

        /// List of Drivers
        std::deque<ReadFactoryT> m_read_driver_factories;
        std::deque<WriteFactoryT> m_write_driver_factories;

}; // End of Disk_Driver_Manager Class

} // end of tmns::image::io namespace