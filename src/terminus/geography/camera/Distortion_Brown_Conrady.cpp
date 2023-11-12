/**
 * @file    Distortion_Brown_Conrady.cpp
 * @author  Marvin Smith
 * @date    11/10/2023
*/
#include <terminus/geography/camera/Distortion_Brown_Conrady.hpp>

namespace tmns::geo::cam {

/*********************************/
/*          Constructor          */
/*********************************/
Distortion_Brown_Conrady::Distortion_Brown_Conrady( const math::Point2d&       principle_point_pitch,
                                                    const std::vector<double>& radial_distortion,
                                                    const std::vector<double>& tangential_distortion,
                                                    double                     tangential_distortion_angle_rad )
    : m_principle_point( principle_point_pitch ),
      m_radial_distortion( radial_distortion ),
      m_centering_distortion( tangential_distortion ),
      m_centering_angle_rad( tangential_distortion_angle_rad )
{
}

/****************************************************/
/*      Get the current distortion parameters       */
/****************************************************/
std::vector<double> Distortion_Brown_Conrady::distortion_parameters() const
{
    std::vector<double> output;
    std::copy( m_principle_point.begin(),
               m_principle_point.end(),
               output.begin() );
    

    std::copy( m_radial_distortion.begin(),
               m_radial_distortion.end(),
               output.end() );
    
    std::copy( m_centering_distortion.begin(),
               m_centering_distortion.end(),
               output.end() );
    
    output.push_back( m_centering_angle_rad );

    return output;
}

/****************************************************/
/*      Set the current distortion parameters       */
/****************************************************/
void Distortion_Brown_Conrady::set_distortion_parameters( const std::vector<double>& params )
{
    m_principle_point   = math::Point2d( { params[0],
                                           params[1] } );
    
    m_radial_distortion = math::Vector3d( { params[2], 
                                            params[3],
                                            params[4] } );
    
    m_centering_distortion = math::Vector2d( { params[5],
                                               params[6] } );

    m_centering_angle_rad = params[7];
}

} // End of tmns::geo::cam namespace