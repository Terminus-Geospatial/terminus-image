/**
 * @file    Interest_Point.cpp
 * @author  Marvin Smith
 * @date    8/11/2023
*/
#include "Interest_Point.hpp"

// Terminus Libraries
#include <terminus/math/Point_Utilities.hpp>

namespace tmns::feature {

/********************************/
/*          Constructor         */
/********************************/
Interest_Point::Interest_Point( float px,
                                float py )
    : m_pixel_loc( { px, py } ),
      m_raster_loc( { (int) std::round( px ),
                      (int) std::round( py ) } )
{
}

/********************************/
/*          Constructor         */
/********************************/
Interest_Point::Interest_Point( const math::Point2f& pixel_loc )
 : m_pixel_loc( pixel_loc ),
   m_raster_loc( math::ToPoint2<int>( (int) std::round( pixel_loc.x() ),
                                      (int) std::round( pixel_loc.y() ) ) )
{
}

} // End of tmns::feature namespace