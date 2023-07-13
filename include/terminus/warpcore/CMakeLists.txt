#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    7/10/2023

set( WARP_INCLUDE_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/image/pixel/Pixel_Base.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/image/pixel/Pixel_RGB.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/image/Image_Base.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/image/Image_Memory.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/io/Image_IO.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/utilities/View_Utilities.hpp
        PARENT_SCOPE )