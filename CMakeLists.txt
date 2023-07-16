#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    July 5, 2023
#

#  Set CMake Version
cmake_minimum_required( VERSION 3.0 FATAL_ERROR )

#  Configure Conan Search Paths
include( "${CMAKE_BINARY_DIR}/conan_toolchain.cmake" )
set( CMAKE_FIND_PACKAGE_PREFER_CONFIG TRUE )

#  Set the Project-Name
project( ${CONAN_PKG_NAME}
            VERSION ${CONAN_PKG_VERSION}
            HOMEPAGE_URL ${CONAN_PKG_URL}
            DESCRIPTION ${CONAN_PKG_DESCRIPTION}
            LANGUAGES CXX
     )

#  Set C++ 20 Support
set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

#  Give Vscode a fighting chance
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Bring in CMake helpers for TERMINUS projects
include( terminus_cmake )

#  Look for dependencies
include("${PROJECT_SOURCE_DIR}/cmake/scripts/Find_Dependencies.cmake")

#  Add Interfaces
add_subdirectory( include/terminus )
add_subdirectory( src/image )

#  Create Library
add_library( ${PROJECT_NAME} SHARED
    ${TERMINUS_IMAGE_INCLUDE_HEADERS}
    $<TARGET_OBJECTS:TERMINUS_IMAGE_CORE>
    $<TARGET_OBJECTS:TERMINUS_IMAGE_IO>
    $<TARGET_OBJECTS:TERMINUS_IMAGE_IO_DRIVERS>
    $<TARGET_OBJECTS:TERMINUS_IMAGE_IO_DRIVERS_GDAL>
    $<TARGET_OBJECTS:TERMINUS_IMAGE_PIXEL>
)

#  Link in dependencies
target_link_libraries( ${PROJECT_NAME}
     Boost::json
     Boost::log
     Boost::log_setup
     Boost::system
     GDAL::GDAL
     terminus_log::terminus_log
     terminus_math::terminus_math
     terminus_outcome::terminus_outcome
)

#  Enable code coverage
if( TERMINUS_IMAGE_ENABLE_COVERAGE )
     terminus_coverage_enable()
endif()

if( TERMINUS_IMAGE_ENABLE_TESTS )
    enable_testing()
    add_subdirectory( tests/unit )
endif()
