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

#  Add Interfaces
add_subdirectory( include/terminus/warpcore )
add_subdirectory( src )

#  Create Library
add_library( ${PROJECT_NAME} INTERFACE
    ${WARP_INCLUDE_HEADERS}
)

#  Link in dependencies
target_link_libraries( ${PROJECT_NAME} INTERFACE
     Boost::headers
     terminus_log::terminus_log
     terminus_outcome::terminus_outcome
)


if(ENABLE_TESTS)
    message( "TESTING ENABLED" )
    add_subdirectory( tests )
endif()