/**
 * @file    Interest_Point.hpp
 * @author  Marvin Smith
 * @date    7/30/2023
*/
#pragma once

// Terminus Libraries
#include <terminus/math/Point.hpp>
#include <terminus/math/VectorN.hpp>

// C++ Libraries
#include <deque>

namespace tmns::feature {

/**
 * @brief Class for organizing feature/interest point data
*/
class Interest_Point
{
    public:

        /**
         * Initial Constructor
        */
        Interest_Point( float x,
                        float y );

    private:

        /// Pixel Location
        math::Point2d m_pixel_loc { { 0, 0 } };

        /// Scale
        float m_scale { 1 };

        /// Raster Coords
        math::Point2i m_raster_loc { { 0, 0 } };

        /// Descriptor Vector
        math::VectorN<float> m_descriptor;

}; // End of Interest_Point class


/// Typedef for Interest_Point_List
typedef std::deque<Interest_Point> Interest_Point_List;

} // End of tmns::feature namespace