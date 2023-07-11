#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    7/10/2023

set( WARP_INCLUDE_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/image/ImageBase.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/io/Image_IO.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/utilities/View_Utilities.hpp
        PARENT_SCOPE )