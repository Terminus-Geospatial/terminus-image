/**
 * @file    Camera_Model_Base.cpp
 * @author  Marvin Smith
 * @date    9/15/2023
 */
#include <terminus/geography/camera/Camera_Model_Base.hpp>

namespace tmns::geo::cam {

/********************************/
/*          Get the pose        */
/********************************/
Result<math::Quaternion> Camera_Model_Base::camera_pose( const math::Point2d& pixel ) const
{
    return outcome::fail( core::error::ErrorCode::NOT_IMPLEMENTED,
                          "Not implemented for camera-model-type: ", 
                          this->type() );
}

} // End of tmns::geo::cam namespace