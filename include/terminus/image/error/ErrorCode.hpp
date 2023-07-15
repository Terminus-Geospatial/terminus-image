/**
 * @file    ErrorCode.hpp
 * @author  Marvin Smith
 * @date    7/10/2023
*/
#pragma once

// Terminus Libraries
#include <terminus/outcome/macros.hpp>

namespace tmns::image::error {

/**
 * Custom ErrorCode enumeration for all WarpCore issues.
*/
enum class ErrorCode { SUCCESS              = 0,
                       UNKNOWN              = 1,
                       FILE_NOT_FOUND       = 2,
                       DRIVER_NOT_FOUND     = 3,
                       UNDEFINED            = 4,
                       INVALID_CHANNEL_TYPE = 5,
                       INVALID_PIXEL_TYPE   = 6,
                       NOT_IMPLEMENTED      = 7  };

} // End of tmns::image::error namespace

// Mark the error code type so that the library knows it is part of the framework
TERMINUS_OUTCOME_MARK_ENUM( tmns::image::error::ErrorCode )