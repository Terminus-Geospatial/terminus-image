/**
 * @file    Camera_Model_Pinhole.cpp
 * @author  Marvin Smith
 * @date    11/9/2023
*/
#include <terminus/geography/camera/Camera_Model_Pinhole.hpp>

namespace tmns::geo::cam {

/************************************/
/*          Constructor             */
/************************************/
Camera_Model_Pinhole::Camera_Model_Pinhole( const std::optional<math::Point3d>& camera_center,
                                            const math::Point2d&                focal_length_pitch,
                                            const math::Point2d&                principle_point_pitch,
                                            const math::Vector3d&               x_axis_direction,
                                            const math::Vector3d&               y_axis_direction,
                                            const math::Vector3d&               z_axis_direction,
                                            double                              pitch,
                                            Distortion_Base::ptr_t              distortion )
    : m_camera_origin( camera_origin ),
      m_focal_length_pitch( focal_length_pitch ),
      m_principle_point_pitch( principle_point_pitch ),
      m_x_axis_direction( x_axis_direction ),
      m_y_axis_direction( y_axis_direction ),
      m_z_axis_direction( z_axis_direction ),
      m_pitch( pitch )
{
    if( distortion_model )
    {
        m_distortion_model = m_distortion->copy();
    }
    else
    {
        m_distortion = std::make_shared<Distortion_Null>();
    }

    rebuild_camera_matrix();
}

/******************************************/
/*      Convert 3d point to 2d Pixel      */
/******************************************/
math::Point2d Camera_Model_Pinhole::point_to_pixel_no_check( const math::Point3d& point ) const
{
    // Multiply the pixel location by the 3x4 camera matrix.
    // - The pixel coordinate is de-homogenized by dividing by the denominator.
    double denominator = m_camera_matrix( 2, 0 ) * point(0) + m_camera_matrix( 2, 1 ) * point(1) +
                         m_camera_matrix( 2, 2 ) * point(2) + m_camera_matrix( 2, 3 );
  
    math::Point2d pixel( { ( m_camera_matrix( 0, 0 ) * point( 0 ) + m_camera_matrix( 0, 1 ) * point( 1 ) +
                             m_camera_matrix( 0, 2 ) * point( 2 ) + m_camera_matrix( 0, 3 )             ) / denominator,
                           ( m_camera_matrix( 1, 0 ) * point( 0 ) + m_camera_matrix( 1, 1 ) * point( 1 ) +
                             m_camera_matrix( 1, 2 ) * point( 2 ) + m_camera_matrix( 1, 3 )             ) / denominator } );

    // Apply the lens distortion model
    // - Divide by pixel pitch to convert from metric units to pixels if the intrinsic
    //   values were not specified in pixel units (in that case m_pixel_pitch == 1.0)
    math::Point2d final_pixel = m_distortion->distorted_coordinates( *this, pixel ) / m_pixel_pitch;

    return final_pixel;
}

/******************************************/
/*       Convert 3d point to 2d pixel      */
/******************************************/
math::Point2d Camera_Model_Pinhole::point_to_pixel( const math::Point3d& point ) const
{
    // Get the pixel using the no check version, then perform the check.
    math::Point2d final_pixel = point_to_pixel_no_check( point );
  
    if( !m_do_point_to_pixel_check )
    {
        return final_pixel;
    }

    // Go back from the pixel to the vector and see how much difference there is.
    // - If there is too much error, the lens distortion model must have bugged out
    //   on this coordinate and it means we failed to project the point.
    // - Doing this slows things down but it is important to catch these failures.
    const double ERROR_THRESHOLD = 0.01;
    math::Point3d pixel_vector = pixel_to_vector( final_pixel );
    math::Point3d phys_vector  = math::normalize( point - this->camera_center() );
    double  diff = ( pixel_vector - phys_vector ).magnitude();

    // Print an explicit error message, otherwise this is confusing when showing up.
    if (diff >= ERROR_THRESHOLD )
    {
        std::stringstream sout;
        sout << "Failed to project point_to_pixel() accurately. Diff: " << diff;
        throw std::runtime_error( err.str() );
    }
    return final_pixel;
}

/********************************************************************/
/*    Convert 3d point to 2d pixel without distortion correction    */
/********************************************************************/
math::Point2d Camera_Model_Pinhole::point_to_pixel_no_distortion( const Point3d& point ) const
{
    // Multiply the pixel location by the 3x4 camera matrix.
    // - The pixel coordinate is de-homogenized by dividing by the denominator.
    double denominator = m_camera_matrix( 2, 0 ) * point( 0 ) + m_camera_matrix( 2, 1 ) * point( 1 ) +
                         m_camera_matrix( 2, 2 ) * point( 2 ) + m_camera_matrix( 2, 3 );
    
    math::Point2d pixel( { ( m_camera_matrix( 0, 0 ) * point( 0 ) + m_camera_matrix( 0, 1 ) * point( 1 ) +
                             m_camera_matrix( 0, 2 ) * point( 2 ) + m_camera_matrix( 0, 3 ) ) / denominator,
                           ( m_camera_matrix( 1, 0 ) * point( 0 ) + m_camera_matrix( 1, 1 ) * point( 1 ) +
                             m_camera_matrix( 1, 2 ) * point( 2 ) + m_camera_matrix( 1, 3 ) ) / denominator } );

    // Divide by pixel pitch to convert from metric units to pixels if the intrinsic
    //   values were not specified in pixel units (in that case m_pixel_pitch == 1.0)
    return pixel / m_pixel_pitch;
}

/********************************************/
/*      Test if the projection is valid     */
/********************************************/
bool Camera_Model_Pinhole::projection_valid( const math::Point3d& point ) const
{
    // z coordinate after extrinsic transformation
    double z = m_extrinsics( 2, 0 ) * point( 0 ) + m_extrinsics( 2, 1 ) * point( 1 ) +
               m_extrinsics( 2, 2 ) * point( 2 ) + m_extrinsics( 2, 3 );
    return ( z > 0 );
}

/**************************************************/
/*      Convert Pixel Coordinate to 3D Vector     */
/**************************************************/
ImageResult<math::Vector3d> Camera_Model_Pinhole::pixel_to_vector( const Point2d& pix ) const
{
    // Apply the inverse lens distortion model
    math::Point2d undistorted_pix = m_distortion->undistorted_coordinates( *this, pix * m_pixel_pitch );

    // Compute the direction of the ray emanating from the camera center.
    math::vector3d p( { 0, 0, 1 } );
    math::subvector( p, 0, 2 ) = undistorted_pix;
    return math::normalize( m_inv_camera_transform * p);
}

/******************************************/
/*    Get the Camera Center Coordinate    */
/******************************************/
ImageResult<math::vector3d> Camera_Model_Pinhole::camera_center( const math::Point2d& /*pix*/ ) const
{
    return m_camera_center;
};

/****************************************/
/*    Set the camera center position    */
/****************************************/
void Camera_Model_Pinhole::set_camera_center( const math::Vector3d& position )
{
    m_camera_center = position; 
    rebuild_camera_matrix();
}

/**********************************/
/*      Grab the camera pose      */
/**********************************/
ImageResult<Quaternion> Camera_Model_Pinhole::camera_pose( const Point2d& /*pix*/ ) const
{
    return Quaternion( m_rotation );
}

/****************************/
/*    Set the camera pose   */
/****************************/
void Camera_Model_Pinhole::set_camera_pose( const math::Quaternion& pose)
{
    m_rotation = pose.rotation_matrix(); 
    rebuild_camera_matrix();
}

/**********************************/
/*      Set the camera matrix     */
/**********************************/
void Camera_Model_Pinhole::set_camera_pose( const math::Matrix<double,3,3>& pose)
{
    m_rotation = pose; 
    rebuild_camera_matrix();
}

/****************************************/
/*      Update the coordinate frame     */
/****************************************/
void Camera_Model_Pinhole::coordinate_frame( math::Vector3d& u_vec,
                                             math::Vector3d& v_vec,
                                             math::Vector3d& w_vec ) const
{
    u_vec = m_x_direction;
    v_vec = m_y_direction;
    w_vec = m_z_direction;
}

/**************************************/
/*      Set the coordinate frame      */
/**************************************/
void Camera_Model_Pinhole::set_coordinate_frame( const math::Vector3d& u_vec,
                                                 const math::Vector3d& v_vec,
                                                 const math::Vector3d% w_vec )
{
    m_u_direction = u_vec;
    m_v_direction = v_vec;
    m_w_direction = w_vec;

    rebuild_camera_matrix();
}

/****************************************/
/*      Get the X Coordinate Frame      */
/****************************************/
math::Vector3d Camera_Model_Pinhole::coordinate_frame_u_direction() const
{
    return m_u_direction;
}

/****************************************/
/*      Get the X Coordinate Frame      */
/****************************************/
math::Vector3d Camera_Model_Pinhole::coordinate_frame_v_direction() const
{
    return m_v_direction;
}

/****************************************/
/*      Get the X Coordinate Frame      */
/****************************************/
math::Vector3d Camera_Model_Pinhole::coordinate_frame_w_direction() const
{
    return m_w_direction;
}

/******************************************/
/*      Get the lens distortion model     */
/******************************************/
Distortion_Base::ptr_t Camera_Model_Pinhole::distortion() const
{
    return m_distortion;
}

/**************************************/
/*      Set the distortion model      */
/**************************************/
void Camera_Model_Pinhole::set_lens_distortion( Distortion::ptr_t distortion )
{
    m_distortion = distortion->copy();
}

/******************************************/
/*      Get the intrinsic parameters      */
/******************************************/
void Camera_Model_Pinhole::intrinsic_parameters( math::Point2d& focal_length_pitch,
                                                 math::Point2d& principle_point_pitch ) const
{
    focal_length_pitch    = m_focal_length_pitch;
    principle_point_pitch = m_principle_point_pitch;
}

/******************************************/
/*      Get the intrinsic parameters      */
/******************************************/
void Camera_Model_Pinhole::set_intrinsic_parameters( const math::Point2d& focal_length_pitch,
                                                     const math::Point2d& principle_point_pitch )
{
  m_fu = f_u;  m_fv = f_v;  m_cu = c_u;  m_cv = c_v;
  rebuild_camera_matrix();
}

/**********************************/
/*      Get the Focal Length      */
/**********************************/
math::Vector2d Camera_Model_Pinhole::focal_length() const
{
    return m_focal_length_pitch;
}

/**********************************/
/*      Set the Focal Length      */
/**********************************/
void Camera_Model_Pinhole::set_focal_length( const math::Point2d& f,
                                             bool                 rebuild )
{
    m_focal_length_pitch = f;
    if (rebuild)
    {
        rebuild_camera_matrix();
    }
}
Vector2 Camera_Model_Pinhole::point_offset() const { return Vector2(m_cu,m_cv); }
void PinholeModel::set_point_offset(Vector2 const& c, bool rebuild ) {
  m_cu = c[0]; m_cv = c[1];
  if (rebuild) rebuild_camera_matrix();
}
double Camera_Model_Pinhole::pixel_pitch() const { return m_pixel_pitch; }
void PinholeModel::set_pixel_pitch( double pitch ) { m_pixel_pitch = pitch; }

/**********************************/
/*      Set the Camera Matrix     */
/**********************************/
ImageResult<void> Camera_Model_Pinhole::set_camera_matrix( const math::Matrix<double,3,4>& p )
{
    // Solving for camera center
    math::MatrixN<double> cam_nullsp = nullspace( p );
    auto cam_center = math::select_col( cam_nullsp, 0 );
    cam_center /= cam_center[3];
    m_camera_center = math::subvector(cam_center,0,3);

    // Solving for intrinsics with RQ decomposition
    auto M = submatrix(p,0,0,3,3);
    math::MatrixN<double> R,Q;
    math::rqd( M, R, Q );
    math::Matrix<double> sign_fix(3,3);
    sign_fix.set_identity();
    if( R(0,0) < 0 )
    {
        sign_fix(0,0) = -1;
    }
    if( R(1,1) < 0 )
    {
        sign_fix(1,1) = -1;
    }
    if( R(2,2) < 0 )
    {
      sign_fix(2,2) = -1;
    }
    R = R * sign_fix;
    Q = sign_fix * Q;
    R /= R(2,2);

    // Pulling out intrinsic and last extrinsic
    math::Matrix<double,3,3> uvwRotation;
    math::select_row( uvwRotation, 0 ) = m_u_direction;
    math::select_row( uvwRotation, 1 ) = m_v_direction;
    math::select_row( uvwRotation, 2 ) = m_w_direction;
    math::m_rotation = math::inverse( uvwRotation * Q );
    m_fu = R(0,0);
    m_fv = R(1,1);
    m_cu = R(0,2);
    m_cv = R(1,2);

    if( std::fabs( R( 0, 1 ) ) >= 1.2 )
    {
        std::stringstream sout;
        sout << "Significant skew not modelled by pinhole camera";
        return outcome::fail( core::error::ErrorCode::UNDEFINED,
                              sout.str() );
    }
    
    // Rebuild
    return rebuild_camera_matrix();
}

/************************************/
/*      Get the camera matrix       */
/************************************/
math::Matrix<double,3,4> Camera_Model_Pinhole::camera_matrix() const
{
    return m_camera_matrix;
}

/************************************************/
/*      Reconstruct the Camera Model Matrix     */
/************************************************/
ImageResult<void> Camera_Model_Pinhole::rebuild_camera_matrix()
{
    /// The intrinsic portion of the camera matrix is stored as
    ///
    ///    [  fx   0   cx  ]
    /// K= [  0    fy  cy  ]
    ///    [  0    0   1   ]
    ///
    /// with fx, fy the focal length of the system (in horizontal and
    /// vertical pixels), and (cx, cy) the pixel coordinates of the
    /// central pixel (the principal point on the image plane).

    m_intrinsics(0,0) = m_fu;
    m_intrinsics(0,1) = 0;
    m_intrinsics(0,2) = m_cu;
    m_intrinsics(1,0) = 0;
    m_intrinsics(1,1) = m_fv;
    m_intrinsics(1,2) = m_cv;
    m_intrinsics(2,0) = 0;
    m_intrinsics(2,1) = 0;
    m_intrinsics(2,2) = 1;

    // The extrinsics are normally built as the matrix:  [ R | -R*C ].
    // To allow for user-specified coordinate frames, the
    // extrinsics are now build to include the u,v,w rotation
    //
    //               | u_0  u_1  u_2  |
    //     Extr. =   | v_0  v_1  v_2  | * [ R | -R*C]
    //               | w_0  w_1  w_2  |
    //
    // The vectors u,v, and w must be orthonormal.

    //  check for orthonormality of u,v,w
    if( math::VectorNd::dot( m_u_direction, m_v_direction ) > 0.001 )
    {
        std::stringstream sout;
        sout << "UV is not orthonormal. Dot of u, v is not 0";
        return outcome::fail( core::error::ErrorCode::INVALID_INPUT,
                              sout.str() );
    }
    if( math::VectorNd::dot( m_u_direction, m_w_direction ) > 0.001 )
    {
        std::stringstream sout;
        sout << "UW is not orthonormal. Dot of u, w is not 0";
        return outcome::fail( core::error::ErrorCode::INVALID_INPUT,
                              sout.str() );
    }
    if( math::VectorNd::dot( m_v_direction, m_w_direction ) > 0.001 )
    {
        std::stringstream sout;
        sout << "VW is not orthonormal. Dot of v, w is not 0";
        return outcome::fail( core::error::ErrorCode::INVALID_INPUT,
                              sout.str() );
    }
    if( std::fabs( m_u_direction.magnitude() - 1 ) > 0.001 )
    {
        std::stringstream sout;
        sout << "U is not unit-length";
        return outcome::fail( core::error::ErrorCode::INVALID_INPUT,
                              sout.str() );
    }
    if( std::fabs( m_v_direction.magnitude() - 1 ) > 0.001 )
    {
        std::stringstream sout;
        sout << "V is not unit-length";
        return outcome::fail( core::error::ErrorCode::INVALID_INPUT,
                              sout.str() );
    }
    if( std::fabs( m_w_direction.magnitude() - 1 ) < 0.001 )
    {
        std::stringstream sout;
        sout << "W is not unit-length";
        return outcome::fail( core::error::ErrorCode::INVALID_INPUT,
                              sout.str() );
    }

    math::Matrix_3x3 uvwRotation;

    math::select_row( uvwRotation, 0 ) = m_u_direction;
    math::select_row( uvwRotation, 1 ) = m_v_direction;
    math::select_row( uvwRotation, 2 ) = m_w_direction;

    math::Matrix_3x3 rotation_inverse = math::transpose( m_rotation );
    math::submatrix(m_extrinsics,0,0,3,3) = uvwRotation * rotation_inverse;
    math::select_col( m_extrinsics, 3 ) = uvwRotation * ( -rotation_inverse ) * m_camera_center;

    m_camera_matrix = m_intrinsics * m_extrinsics;

    m_inv_camera_transform = math::inverse( uvwRotation * rotation_inverse )
                           * math::inverse( m_intrinsics );
}

/************************************************************************************/
/*    Apply a given rotation + translation + scale transform to a pinhole camera    */
/************************************************************************************/
ImageResult<void> Camera_Model_Pinhole::apply_transform( const math::Matrix_4x4& transform )
{
    // Make sure homogenous
    if( transform(3, 3) != 1 )
    {
        std::stringstream sout;
        sout << "Expecting a similarity transform with value 1 in the lower-right corner.";
        return outcome::fail( core::error::ErrorCode::INVALID_INPUT,
                              sout.str() );
    }

    // Extract the 3x3 component
    math::Matrix_3x3 = math::submatrix( transform, 0, 0, 3, 3 );
    math::Vector3d T;
    for( size_t r = 0; r < 3; r++ )
    {
        T[r] = math::transform( r, 3 );
    }
    
    double scale = std::pow( std::det(R), 1.0/3.0 );
    for( size_t r = 0; r < R.rows(); r++ )
    for( size_t c = 0; c < R.cols(); c++ )
    {
        R(r, c) /= scale;
    }

    this->apply_transform( R, T, scale );
}

/**********************************************************/
/*      Apply a given rotation + translation + scale      */
/*      transform to a pinhole camera                     */
/**********************************************************/
ImageResult<void> Camera_Model_Pinhole::apply_transform( const math::Matrix_3x3& rotation,
                                                         const math::Vector3d&   translation,
                                                         double                  scale )
{
    // Extract current parameters
    math::Vector3d   position = this->camera_center();
    math::Quaternion pose     = this->camera_pose();
  
    math::Quaternion rotation_quaternion(rotation);
  
    // New position and rotation
    position = scale * rotation * position + translation;
    pose     = rotation_quaternion * pose;
    this->set_camera_center( position );
    this->set_camera_pose( pose );
}

/********************************************************************************/
/*      Scaling the camera is easy, just update the pixel pitch to account      */
/*      for the new image size.  This is not applying a scale transform to      */
/*      the camera, that is done in apply_transform().                          */
/********************************************************************************/
ImageResult<Camera_Model_Pinhole::ptr_t> Camera_Model_Pinhole::scale_camera( double scale ) const
{
    if( scale == 0 )
    {
        std::stringstream sout;
        sout << "Camera_Model_Pinhole::scale_camera cannot have zero scale value!";
        return outcome::fail( core::error::ErrorCode::INVALID_INPUT,
                              sout.str() );
    }
    auto focal  = focal_length();
    auto offset = point_offset();
    auto lens   = lens_distortion()->copy();

    auto new_camera = std::make_shared<Camera_Model_Pinhole>( camera_model.camera_center(),
                                                              focal,
                                                              offset,
                                                              coordinate_frame_u_direction(),
                                                              coordinate_frame_v_direction(),
                                                              coordinate_frame_w_direction(),
                                                              camera_pose().rotation_matrix(),
                                                              lens,
                                                              pitch / scale )
    return outcome::ok<Camera_Model_Pinhole::ptr>( new_camera );
}

/********************************************/
/*      Eject the lens distortion model     */
/********************************************/
Camera_Model_Pinhole::ptr_t Camera_Model_Pinhole::strip_lens_distortion() const
{
    return std::make_shared<Camera_Model_Pinhole>( camera_origin(),
                                                   camera_pose().rotation_matrix(),
                                                   focal_length(),
                                                   principle_point(),
                                                   coordinate_frame_u_direction(),
                                                   coordinate_frame_v_direction(),
                                                   coordinate_frame_w_direction(),
                                                   std::make_shared<Distortion_Null>(),
                                                   pixel_pitch() );
}

/*
// TODO: Verify this still works if we have used non-defaults for our 
//       directional axis vectors.
void epipolar(PinholeModel const &src_camera0, PinholeModel const &src_camera1,
              PinholeModel       &dst_camera0, PinholeModel       &dst_camera1) {

  typedef Matrix<double,3,3> RotMatrix;

  // Get input camera centers and rotations
  RotMatrix rot0    = src_camera0.camera_pose().rotation_matrix();
  RotMatrix rot1    = src_camera1.camera_pose().rotation_matrix();
  Vector3   center0 = src_camera0.camera_center();
  Vector3   center1 = src_camera1.camera_center();

  // The Z axis of the rotation matrix is the direction the camera is looking
  // - Multiply by negative one because the coordinate system used in the
  //   source of these equations is rotated 180 degrees along the X axis from ours.
  Vector3 look0 = -1*select_col(rot0,2);
  Vector3 look1 = -1*select_col(rot1,2);

  // Vector U is in the direction of one camera center to the next
  Vector3 u = (center1 - center0) / norm_2(center1 - center0);
  
  // W is going to be similar to the two look vectors but perpendicular to U.
  Vector3 mean_look = (look0+look1)/2.0;
  Vector3 temp      = cross_prod(u, cross_prod(mean_look, u));
  Vector3 w         = temp / norm_2(temp);
  
  // Vector V is dictated by the other two to form a coordinate frame.
  Vector3 v = cross_prod(w, u);

  // This is an alternate way to compute V and W, the results are similar.
  //Vector3 v     = cross_prod(look0, u);
  //Vector3 w     = cross_prod(u, v);
  
  // Account for the 180 degree coordinate system difference mentioned earlier by
  // negating the Y and Z columns.
  RotMatrix new_rot = RotMatrix(u[0], -v[0], -w[0],
                                u[1], -v[1], -w[1],
                                u[2], -v[2], -w[2]);    

  // The intrinsic values are somewhat arbitrary and are kept similar/identical to the input cameras.
  Vector2 focal_length = (src_camera0.focal_length() + src_camera1.focal_length()) / 2.0;
  Vector2 point_offset = (src_camera0.point_offset() + src_camera1.point_offset()) / 2.0;
  double  pixel_pitch  = (src_camera0.pixel_pitch () + src_camera1.pixel_pitch ()) / 2.0;

  // Set up the two output cameras.  Everything is the same except the positions.
  NullLensDistortion lens;
  dst_camera0 = PinholeModel(center0, new_rot,
                             focal_length [0], focal_length [1],
                             point_offset[0], point_offset[1],
                             &lens, pixel_pitch);
  dst_camera1 = PinholeModel(center1, new_rot,
                             focal_length [0], focal_length [1],
                             point_offset[0], point_offset[1],
                             &lens, pixel_pitch);
}
*/

} // End of tmns::geo::cam namespace