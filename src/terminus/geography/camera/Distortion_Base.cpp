/**
 * @file    Distortion.cpp
 * @author  Marvin Smith
 * @date    11/10/2023
 */
#include <terminus/geography/camera/Distortion.hpp>


namespace tmns::geo::cam {

/****************************************************************/
/*          Convert from Undistorted to Distorted Coords        */
/****************************************************************/
math::Point2d Distortion_Base::to_distorted( const std::shared_ptr<Camera_Model_Pinhole> camera_model,
                                             const math::Point2d&                        pixel_coord ) const
{

}

/****************************************************************/
/*          Convert from Distorted to Undistorted Coords        */
/****************************************************************/
math::Point2d Distortion_Base::to_undistorted( const std::shared_ptr<Camera_Model_Pinhole> camera_model,
                                               const math::Point2d&                        pixel_coord ) const
{

}

/********************************************/
/*      Check if we have fast distortion    */
/********************************************/
bool Distortion_Base::has_fast_distort() const
{
    return false;
}

/**********************************************/
/*      Check if we have fast undistortion    */
/**********************************************/
bool Distortion_Base::has_fast_undistort() const
{
    return false;
}

/*******************************************/
/*      Get Distortion Parameters (none)   */
/*******************************************/
std::vector<double> Distortion_Base::distortion_parameters() const
{
    return std::vector<double>();
}

/*******************************************/
/*      Get Distortion Parameters (none)   */
/*******************************************/
void Distortion_Base::set_distortion_parameters( const std::vector<double>& params )
{
    // no-op
}

} // End of tmns::geo::cam namespace