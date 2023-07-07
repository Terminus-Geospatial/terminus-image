#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    July 5, 2023
#

#  Set CMake Version
cmake_minimum_required( VERSION 3.0 FATAL_ERROR )

#  Set the Project-Name
project( WarpCore )

#  Set C++ 20 Support
set( CMAKE_CXX_STANDARD 20 )

#  Look for dependencies
include("${PROJECT_SOURCE_DIR}/cmake/scripts/Find_Dependencies.cmake")

#  Build WarpCore
add_subdirectory( src )

if(ENABLE_TESTS)
  add_subdirectory( tests )
endif()