/**
 * @file    File_Collection_Utilities.hpp
 * @author  Marvin Smith
 * @date    8/26/2023
 */
#pragma once

// C++ Libraries
#include <filesystem>
#include <vector>

// Terminus Libraries
#include <terminus/core/error/ErrorCategory.hpp>
#include <terminus/geography/camera/Camera_Model_Base.hpp>

namespace tmns::image::cx::file {

/**
 * Parse the INI file and return the results.
*/
Result<void> parse_toml_collection_file( const std::filesystem::path&         input_path,
                                         std::vector<std::filesystem::path>&  image_list,
                                         geo::cam::Camera_Model_Base::ptr_t&  global_intrinsics );

} // End of tmns::image::cx::file namespace