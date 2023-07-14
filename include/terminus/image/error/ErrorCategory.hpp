/**
 * @file    ErrorCategory.hpp
 * @author  Marvin Smith
 * @date    7/10/2023
*/
#pragma once

// Terminus Libraries
#include <terminus/outcome/ErrorCategory.hpp>
#include <terminus/outcome/Result.hpp>
#include <terminus/outcome/macros.hpp>

// Terminus Image Libraries
#include "ErrorCode.hpp"

namespace tmns::image::error {

/**
 * Custom WarpCore error category for mapping all error codes to custom error types.
*/
class ErrorCategory : public tmns::outcome::ErrorCategory<ErrorCategory>
{
    protected:

        const char* name_() const noexcept override
        {
            return "Error";
        }

        std::string message_(int c) const override
        {
            switch( static_cast<ErrorCode>(c) )
            {
                case ErrorCode::SUCCESS:
                    return "SUCCESS";
                case ErrorCode::UNKNOWN:
                    return "UNKNOWN";
                case ErrorCode::FILE_NOT_FOUND:
                    return "FILE_NOT_FOUND";
                case ErrorCode::DRIVER_NOT_FOUND:
                    return "DRIVER_NOT_FOUND";
                case ErrorCode::UNDEFINED:
                    return "UNDEFINED";
                default:
                    return "UNKNOWN";
            }
        }
}; // End of ErrorCategory class

// Associate the custom error category with your custom error code
TERMINUS_OUTCOME_ASSOCIATE_ERROR_CATEGORY( ErrorCategory, ErrorCode )

} // End of tmns::image::error namespace

// Define a convenient alias for the `Result` type that uses your error codes
template <class ValueT>
using ImageResult = tmns::outcome::Result<ValueT,tmns::image::error::ErrorCode>;
