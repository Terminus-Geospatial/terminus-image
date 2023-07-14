/**
 * @file    Disk_Driver_Manager.hpp
 * @author  Marvin Smith
 * @date    7/13/2023
*/
#pragma once

/// Terminus Libraries
#include "../Image_Resource_Disk.hpp"

// C++ Libraries
#include <memory>

namespace tmns::image::io {

/**
 * Relatively simple class for storing file input and output drivers.
*/
class Disk_Driver_Manager
{
    public:

        /// Pointer Type
        typedef std::shared_ptr<Disk_Driver_Manager> ptr_t;

        /**
         * Create a Driver-Manager using the default configuration
         *
         * @note The order by which a driver is chosen is the order it is registered.
        */
        static constexpr Disk_Driver_Manager::ptr_t create_defaults()
        {
            // Create new instance
            auto instance = std::make_shared<Disk_Driver_Manager>();

            // Register each driver

            return instance;
        }

        /**
         * Select a driver based on the file.
        */
        outcome::Result<Image_Resource_Disk::ptr_t> pick_driver( const std::filesystem::path& pathname ) const;

    private:

        /// Default Constructor
        Driver_Manager() = default;

        /// List of Drivers
        std::deque<Image_Resource_Disk::ptr_t> m_drivers;

}; // End of Driver_Manager Class

} // end of tmns::image::io namespace