/**
 * @file     Image_Resource_Memory_GDAL.hpp
 * @author   Marvin Smith
 * @date     7/13/2023
*/
#pragma once


namespace tmns::image::io::gdal {

/**
 * GDAL Driver for loading data in memory
*/
class Image_Resource_Memory_GDAL : public Image_Resource_Memory,
                                   boost::noncopyable
{

}; // End of Image_Resource_Memory_GDAL class

} // End of tmns::image::io::gdal