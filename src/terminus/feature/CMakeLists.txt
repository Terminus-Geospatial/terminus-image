#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    7/30/2023

add_subdirectory( drivers )

#  Build this library
include_directories( ${CMAKE_SOURCE_DIR}/include/terminus/feature )

add_library( TERMINUS_FEATURE_BASE OBJECT
                Detector_Base.cpp
                Interest_Point.cpp )