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

#  Give Vscode a fighting chance
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#  Add Interfaces
add_subdirectory( include/terminus )
add_subdirectory( src/image )

#  Create Library
add_library( ${PROJECT_NAME} SHARED
    ${TERMINUS_IMAGE_INCLUDE_HEADERS}
    $<TARGET_OBJECTS:TERMINUS_IMAGE_CORE>
    $<TARGET_OBJECTS:TERMINUS_IMAGE_IO>
    $<TARGET_OBJECTS:TERMINUS_IMAGE_IO_DRIVERS>
    $<TARGET_OBJECTS:TERMINUS_IMAGE_PIXEL>
)

#  Link in dependencies
target_link_libraries( ${PROJECT_NAME} PUBLIC
     Boost::headers
     terminus_log::terminus_log
     terminus_math::terminus_math
     terminus_outcome::terminus_outcome
)


if(ENABLE_TESTS)
    message( "TESTING ENABLED" )
    add_subdirectory( tests )
endif()
