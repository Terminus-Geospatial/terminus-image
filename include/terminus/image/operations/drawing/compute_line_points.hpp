/**
 * @file    compute_line_points.hpp
 * @author  Marvin Smith
 * @date    8/13/2023
*/
#pragma once

// Terminus Libraries
#include <terminus/log/utility.hpp>
#include <terminus/math/Point.hpp>
#include <terminus/math/Rectangle.hpp>

// Terminus Image Libraries
#include "Drawing_Enums.hpp"

namespace tmns::image::ops::drawing {

/**
 * Compute the points of a line for a 1-pixel thin line.
 * 
 * @param point1
 * @param point2
 * @param color
 * @param overlap_mode
 * @param[out] output
 * 
 * @returns status of the operation.
*/
template <typename PixelT>
ImageResult<void> compute_line_points_thin( const tmns::math::Point2i&                   point1,
                                            const tmns::math::Point2i&                   point2,
                                            const PixelT&                                color,
                                            Line_Overlap_Mode                            overlap_mode,
                                            std::shared_ptr<blob::Uniform_Blob<PixelT>>& output )
{
    tmns::log::trace( ADD_CURRENT_LOC(),
                      "Start of Method.\n  P1: ", 
                      point1.to_string(),
                      "\n  P2: ", 
                      point2.to_string() );
    int error;
    auto p1 = point1;
    auto p2 = point2;

    tmns::math::Rect2i point_rect( p1,
                                   p2 );

    // If either axis is the same, then draw a box
    if( p1.x() == p2.x() ||
        p1.y() == p2.y() )
    {
        for( int c = point_rect.bl().x(); c <= point_rect.tr().x(); c++ )
        for( int r = point_rect.bl().y(); r <= point_rect.tr().y(); r++ )
        {
            output->insert( c, r, 0, color );
        }
    }
    else
    {
        // calculate direction
        auto delta = p2 - p1;
        tmns::math::Point2i step { { 1, 1 } };
        if( delta.x() < 0 )
        {
            delta.x() = -delta.x();
            step.x() = -1;
        }
        if( delta.y() < 0 )
        {
            delta.y() = -delta.y();
            step.y() = -1;
        }
        
        tmns::math::Point2i delta_x2( { delta.x() << 1,
                                        delta.y() << 1 } );
    
        // Add starting pixel
        output->insert( p1, color );

        if ( delta.x() > delta.y() )
        {
            // start value represents a half step in Y direction
            error = delta_x2.y() - delta.x();
        
            while ( p1.x() != p2.x() )
            {
                // step in main direction
                p1.x() += step.x();
                if( error >= 0 )
                {
                    if ( overlap_mode & Line_Overlap_Mode::MAJOR )
                    {
                        output->insert( p1, color );
                    }

                    // change Y
                    p1.y() += step.y();
                
                    if( overlap_mode & Line_Overlap_Mode::MINOR)
                    {
                        // draw pixel in minor direction before changing
                        output->insert( tmns::math::Point2i( { p1.x() - step.x(),
                                                               p1.y() } ),
                                        color );
                    }
                    error -= delta_x2.x();
                }
                error += delta_x2.y();

                output->insert( p1, color );
            }
        }
        else
        {
            error = delta_x2.x() - delta.y();
            while( p1.y() != p2.y() )
            {
                p1.y() += step.y();
                if( error >= 0 )
                {
                    if( overlap_mode & Line_Overlap_Mode::MAJOR )
                    {
                        output->insert( p1, color );
                    }
                    p1.x() += step.x();
                    if( overlap_mode & Line_Overlap_Mode::MINOR )
                    {
                        output->insert( tmns::math::Point2i( { p1.x(),
                                                               p1.y() - step.y() } ),
                                       color );
                    }
                    error -= delta_x2.y();
                }
                error += delta_x2.x();
                output->insert( p1, color );
            }
        }
    }

    return tmns::outcome::ok();
}

/**
 * Return a list of pixel coordinates representing the line to draw
 * https://github.com/ArminJo/Arduino-BlueDisplay/blob/master/src/LocalGUI/ThickLine.hpp
*/
template <typename PixelT>
ImageResult<void> compute_line_points( const tmns::math::Point2i&                  p1_orig,
                                       const tmns::math::Point2i&                  p2_orig,
                                       const PixelT&                               color,
                                       int                                         thickness,
                                       Line_Overlap_Mode                           overlap_mode,
                                       std::shared_ptr<blob::Uniform_Blob<PixelT>> output )
{
    tmns::log::trace( ADD_CURRENT_LOC(),
                      "Start of Method.\n  P1: ", 
                      p1_orig.to_string(),
                      "\n  P2: ", 
                      p2_orig.to_string(),
                      "\n  Thickness: ",
                      thickness );

    // Make sure blob is initialized
    if( !output )
    {
        output = std::make_shared<blob::Uniform_Blob<PixelT>>( color );
    }

    // Create output
    auto p1 = p1_orig;
    auto p2 = p2_orig;
    int thickness_mode = Line_Thickness_Mode::DRAW_CLOCKWISE;

    // If either axis is the same, then draw a box
    if( p1.x() == p2.x() ||
        p1.y() == p2.y() )
    {
        math::Rect2i point_rect_pre( p1, p2 );
        auto point_rect = point_rect_pre.expand( thickness / 2 );
        for( int c = point_rect.bl().x(); c <= point_rect.tr().x(); c++ )
        for( int r = point_rect.bl().y(); r <= point_rect.tr().y(); r++ )
        {
            output->insert( c, r, 0, color );
        }
        return outcome::ok();
    }

    // If thickness is a single line, or a fill, continue
    if( thickness <= 1 )
    {
        return compute_line_points_thin<PixelT>( p1_orig,
                                                 p2_orig,
                                                 color,
                                                 overlap_mode,
                                                 output );
    }

    /**
     * For coordinate system with 0.0 top left
     * Swap X and Y delta and calculate clockwise (new delta X inverted)
     * or counterclockwise (new delta Y inverted) rectangular direction.
     * The right rectangular direction for LINE_OVERLAP_MAJOR toggles with each octant
     */
    auto delta = p2 - p1;
    tmns::math::Point2i step { { 1, 1 } };

    // mirror 4 quadrants to one and adjust deltas and stepping direction
    bool swap = true; // count effective mirroring
    int error;

    if( delta.x() < 0 )
    {
        delta.x() = -delta.x();
        step.x() = -1;
        swap = !swap;
    } 
    if( delta.y() < 0 )
    {
        delta.y() = -delta.y();
        step.y() = -1;
        swap = !swap;
    }
    
    tmns::math::Point2i delta_x2( { delta.x() << 1,
                                    delta.y() << 1 } );
    
    // adjust for right direction of thickness from line origin
    int draw_start_adj_count = thickness / 2;
    
    if( thickness_mode == Line_Thickness_Mode::DRAW_COUNTERCLOCKWISE )
    {
        draw_start_adj_count = thickness - 1;
    }
    else if( thickness_mode == Line_Thickness_Mode::DRAW_CLOCKWISE )
    {
        draw_start_adj_count = 0;
    }

    /*
     * Now delta* are positive and step* define the direction
     * swap is false if we mirrored only once
     */
    // which octant are we now
    if( delta.x() >= delta.y() )
    {
        // Octant 1, 3, 5, 7 (between 0 and 45, 90 and 135, ... degree)
        if( swap )
        {
            draw_start_adj_count = ( thickness - 1 ) - draw_start_adj_count;
            step.y() = -step.y();
        }
        else
        {
            step.x() = -step.x();
        }

        /*
         * Vector for draw direction of the starting points of lines is rectangular and counterclockwise to main line direction
         * Therefore no pixel will be missed if LINE_OVERLAP_MAJOR is used on change in minor rectangular direction
         */
        // adjust draw start point
        error = delta_x2.y() - delta.x();
        for( int i = draw_start_adj_count; i > 0; i-- )
        {
            // change X (main direction here)
            p1.x() -= step.x();
            p2.x() -= step.x();
            if( error >= 0 )
            {
                // change Y
                p1.y() -= step.y();
                p2.y() -= step.y();
                error -= delta_x2.x();
            }
            error += delta_x2.y();
        }

        // draw start line. We can alternatively use drawLineOverlap(aXStart, aYStart, aXEnd, aYEnd, LINE_OVERLAP_NONE, aColor) here.
        {
            auto result = compute_line_points_thin<PixelT>( p1,
                                                            p2,
                                                            color,
                                                            Line_Overlap_Mode::BOTH,
                                                            output );
            if( result.has_error() )
            {
                return tmns::outcome::fail( tmns::core::error::ErrorCode::UNDEFINED,
                                            "Problem with computing line: ", 
                                            result.error().message() );
            }
        }

        // draw thickness number of lines
        error = delta_x2.y() - delta.x();
        
        bool overlap = 0;
        for( int i = thickness; i > 1; i-- )
        {
            // change X (main direction here)
            p1.x() += step.x();
            p2.x() += step.x();
            
            overlap = Line_Overlap_Mode::BOTH;
            if( error >= 0 )
            {
                // change Y
                p1.y() += step.y();
                p2.y() += step.y();
                error  -= delta_x2.x();

                /*
                 * Change minor direction reverse to line (main) direction
                 * because of choosing the right (counter)clockwise draw vector
                 * Use LINE_OVERLAP_MAJOR to fill all pixel
                 *
                 * EXAMPLE:
                 * 1,2 = Pixel of first 2 lines
                 * 3 = Pixel of third line in normal line mode
                 * - = Pixel which will additionally be drawn in LINE_OVERLAP_MAJOR mode
                 *           33
                 *       3333-22
                 *   3333-222211
                 * 33-22221111
                 *  221111                     /\
                 *  11                          Main direction of start of lines draw vector
                 *  -> Line main direction
                 *  <- Minor direction of counterclockwise of start of lines draw vector
                 */
                overlap_mode = Line_Overlap_Mode::MAJOR;
            }

            error += delta_x2.y();
            {
                auto result = compute_line_points_thin<PixelT>( p1,
                                                                p2,
                                                                color,
                                                                overlap_mode,
                                                                output );
                if( result.has_error() )
                {
                    return tmns::outcome::fail( tmns::core::error::ErrorCode::UNDEFINED,
                                                "Problem with computing line: ", 
                                                result.error().message() );
                }
            }
        }
    }
    else
    {
        // the other octant 2, 4, 6, 8 (between 45 and 90, 135 and 180, ... degree)
        if( swap )
        {
            step.x() = -step.x();
        }
        else
        {
            draw_start_adj_count = ( thickness - 1 ) - draw_start_adj_count;
            step.y() = -step.y();
        }
        
        // adjust draw start point
        error = delta_x2.x() - delta.y();
        
        for( int i = draw_start_adj_count; i > 0; i--)
        {
            p1.y() -= step.y();
            p2.y() -= step.y();
            if( error >= 0 )
            {
                p1.x() -= step.x();
                p2.x() -= step.x();
                error  -= delta_x2.y();
            }
            error += delta_x2.x();
        }

        //draw start line
        {
            auto result = compute_line_points_thin<PixelT>( p1,
                                                            p2,
                                                            color,
                                                            Line_Overlap_Mode::NONE,
                                                            output );
            if( result.has_error() )
            {
                return tmns::outcome::fail( tmns::core::error::ErrorCode::UNDEFINED,
                                            "Problem with computing line: ", 
                                            result.error().message() );
            }
        }
        
        // draw thickness number of lines
        error = delta_x2.x() - delta.y();

        for( int i = thickness; i > 1; i-- )
        {
            p1.y() += step.y();
            p2.y() += step.y();

            overlap_mode = Line_Overlap_Mode::NONE;
            if( error >= 0 )
            {
                p1.x() += step.x();
                p2.x() += step.x();
                error  -= delta_x2.y();
                overlap_mode = Line_Overlap_Mode::MAJOR;
            }
            error += delta_x2.x();
            
            {
                auto result = compute_line_points_thin<PixelT>( p1,
                                                                p2,
                                                                color,
                                                                overlap_mode,
                                                                output );
                if( result.has_error() )
                {
                    return tmns::outcome::fail( tmns::core::error::ErrorCode::UNDEFINED,
                                                "Problem with computing line: ", 
                                                result.error().message() );
                }
            }
        }
    }

    return tmns::outcome::ok();
}


} // End of tmns::image::ops::drawing namespace