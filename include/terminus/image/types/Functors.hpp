/**
 * @file    Functors.hpp
 * @author  Marvin Smith
 * @date    8/2/2023
*/
#pragma once

namespace tmns::image {

/**
 * Forces functors to use a particular type
*/
template <typename T>
struct Return_Fixed_Type
{
    template <typename Args>
    struct result
    {
        typedef T type;
    }; // End of result struct
}; // End of Return_Fixed_Type class

} // End of tmns::image namespace