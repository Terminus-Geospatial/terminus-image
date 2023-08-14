/**
 * @file    Drawing_Functions.hpp
 * @author  Marvin Smith
 * @date    8/13/2023
*/
#pragma once

namespace tmns::image::ops {

/**
 * Line drawing thick mode
*/
enum Line_Thickness_Mode
{
    DRAW_COUNTERCLOCKWISE = 0,
    DRAW_CLOCKWISE        = 1,
};

/**
 * Line overlapping mode
*/
enum Line_Overlap_Mode
{
    NONE  = 0,
    MAJOR = 1,
    MINOR = 2,
    BOTH  = 3,
};


} // End of tmns::image::ops