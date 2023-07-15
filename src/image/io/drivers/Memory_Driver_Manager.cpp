/**
 * @file    Memory_Driver_Manager.cpp
 * @author  Marvin Smith
 * @date    7/14/2023
*/
#include "Memory_Driver_Manager.hpp"

namespace tmns::image {

/************************************************************************************/
/*          Pick the appropriate driver in the list for processing the dataset      */
/************************************************************************************/
ImageResult<Image_Resource_Memory::ptr_t> pick_driver( const std::filesystem::path& pathname ) const
{
    typedef Image_Resource_Memory::ptr_t ResT;
    for( const auto& driver : m_drivers )
    {
        if( driver->image_is_supported( pathname ) )
        {
            return outcome::ok<ResT>( driver->create( pathname ) );
        }
    }
    return outcome::fail( error::ErrorCode::DRIVER_NOT_FOUND );
}

}