/**
 * @file    ErrorCategory.hpp
 * @author  Marvin Smith
 * @date    7/10/2023
*/
#pragma once

// Terminus Libraries
#include <terminus/outcome/ErrorCategory.hpp>
#include <terminus/outcome/macros.hpp>

namespace tmns::warp::error {

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
            switch( static_cast<IoErrorCode>(c) )
            {
                case IoErrorCode::SUCCESS:
                    return "SUCCESS";
                case IoErrorCode::UNKNOWN:
                    return "UNKNOWN";
                case IoErrorCode::FILE_NOT_FOUND:
                    return "FILE_NOT_FOUND";
                default:
                    return "UNKNOWN";
            }
        }
}; // End of ErrorCategory class

// Associate the custom error category with your custom error code
TERMINUS_OUTCOME_ASSOCIATE_ERROR_CATEGORY( ErrorCategory, ErrorCode )

// Define a convenient alias for the `Result` type that uses your error codes
template <class ValueT>
using Result = tmns::outcome::Result<ValueT,ErrorCode>;

} // End of tmns::warp::error namespace