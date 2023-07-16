#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    7/10/2023

#  Configure GoogleTest
find_package( GTest REQUIRED )
include( GoogleTest )

include_directories( ${CMAKE_SOURCE_DIR}/include )

set( TEST ${PROJECT_NAME}_test )
add_executable( ${TEST}
    io/TEST_read_image.cpp
    io/drivers/gdal/TEST_GDAL_Codes.cpp
    io/drivers/gdal/TEST_GDAL_Utilities.cpp
)

target_link_libraries( ${TEST} PRIVATE
    GTest::gmock_main
    GTest::gtest_main
    ${PROJECT_NAME}
)

gtest_discover_tests( ${TEST} )

#  Copy Unit-Test Data
#file( COPY ${CMAKE_SOURCE_DIR}/data/unit-test-data
#      DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data )