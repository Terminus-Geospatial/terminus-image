#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    9/21/2023
#
#    Purpose:  Build the Geography Coordinate APIs

#  Build this library
include_directories( ${CMAKE_SOURCE_DIR}/include/terminus/geography/coordinate )

add_library( TERMINUS_GEOGRAPHY_COORDINATE OBJECT
                Datum.cpp )