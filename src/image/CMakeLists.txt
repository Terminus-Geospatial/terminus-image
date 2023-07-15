#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    7/10/2023

#  Add include paths
include_directories( TERMINUS_IMAGE_PIXEL PRIVATE
                     ${Boost_INCLUDE_DIRS}
                     ${terminus_log_INCLUDE_DIRS}
                     ${terminus_math_INCLUDE_DIRS}
                     ${terminus_outcome_INCLUDE_DIRS}
)

#  Process all subdirectory objects
add_subdirectory( io )
add_subdirectory( pixel )

#  Build this library
include_directories( ${CMAKE_SOURCE_DIR}/include/terminus/image )

add_library( TERMINUS_IMAGE_CORE OBJECT
                Image_Buffer.cpp
                Image_Format.cpp
                Image_Resource_Base.cpp )

