/**
 * @file    ErrorCode.hpp
 * @author  Marvin Smith
 * @date    7/10/2023
*/
#pragma once

// Terminus Libraries
#include <terminus/outcome/macros.hpp>

namespace tmns::warp::error {

/**
 * Custom ErrorCode enumeration for all WarpCore issues.
*/
enum class ErrorCode { SUCCESS = 0,
                       UNKNOWN = 1,
                       FILE_NOT_FOUND = 2 };

// Mark the error code type so that the library knows it is part of the framework
TERMINUS_OUTCOME_MARK_ENUM( ErrorCode )

} // End of tmns::warp::error namespace