/**
 * @file    Distortion_Null.cpp
 * @author  Marvin Smith
 * @date    11/10/2023
*/
#include <terminus/geography/camera/Distortion_Null.hpp>


namespace tmns::geo::cam {

/********************************************************/
/*          Convert to Distorted Coordinates            */
/********************************************************/
math::Point2d Distortion_Null::to_distorted( const std::shared_ptr<Camera_Model_Pinhole> camera_model,
                                             const math::Point2d&                        pixel_coord ) const
{
    return pixel_coord;
}

/**********************************************************/
/*          Convert to Undistorted Coordinates            */
/**********************************************************/
math::Point2d Distortion_Null::to_undistorted( const std::shared_ptr<Camera_Model_Pinhole> camera_model,
                                               const math::Point2d&                        pixel_coord ) const
{
    return pixel_coord;
}

/********************************************/
/*      Check if Fast Distort Exists        */
/********************************************/
bool Distortion_Null::has_fast_distort() const
{
    return true;
}

/**********************************************/
/*      Check if Fast Undistort Exists        */
/**********************************************/
bool Distortion_Null::has_fast_undistort() const 
{
    return true;
}

/****************************************************/
/*          Get the distortion parameters           */
/****************************************************/
std::vector<double> Distortion_Null::distortion_parameters() const
{
    return std::vector<double>();
}

/************************************************************/
/*          Get the number of distortion parameters         */
/************************************************************/
int Distortion_Null::num_dist_params() const
{
    return 0;
}

/************************************/
/*          Name the Model          */
/************************************/
std::string Distortion_Null::name() const
{
    return "Distortion_Null";
}

/************************************/
/*          Scale the Model         */
/************************************/
ImageResult<void> Distortion_Null::scale( double scale )
{
    // do nothing
    return outcome::ok();
}

} // End of tmns::geo::cam namespace