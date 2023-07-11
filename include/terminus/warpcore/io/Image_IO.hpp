/**
 * @file    Image_IO.hpp
 * @author  Marvin Smith
 * @date    7/10/2023
*/
#pragma once

// Terminus Libraries
#include "../error/ErrorCode.hpp"

namespace tmns::warp::io {

error::Result<> Read_Image();

} // End of tmns::warp::io namespace