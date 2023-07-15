/**
 * @file    GDAL_Utilities.hpp
 * @author  Marvin Smith
 * @date    7/15/2023
*/
#pragma once

// External Terminus Libraries
#include <terminus/log/Logger.hpp>
#include <terminus/outcome/Result.hpp>

// Terminus Libraries
#include "../../../pixel/Pixel_Format_Enum.hpp"

// GDAL Libraries
#include <gdal.h>
#include <gdal_priv.h>

// C++ Libraries
#include <mutex>
#include <tuple>
#include <vector>

namespace tmns::image::io::gdal {

/**
 * Initialize GDAL for use
*/
ImageResult<void> Initialize_GDAL();

/**
 * Get a reference to the master GDAL lock
*/
std::mutex& get_master_gdal_mutex();

/**
 * @brief Get a reference to the logger and mutex
*/
log::Logger& get_master_gdal_logger();

/**
 * Method for destrying GDAL even if dataset is null
*/
void GDAL_Deleter_Null_Okay( GDALDatasetH dataset );

/**
 * Method to convert the GDAL Raster Codes into a composite pixeltype.
*/
ImageResult<Pixel_Format_Enum> gdal_driver_to_pixel_type( const std::vector<std::tuple<std::vector<int>,Pixel_Format_Enum>>& reference_lut,
                                                          const std::vector<int>&                                            channel_codes );



} // end of tmns::image::io::gdal namespace