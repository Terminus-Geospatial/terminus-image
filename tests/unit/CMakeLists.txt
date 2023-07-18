#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    7/10/2023

#  Configure GoogleTest
find_package( GTest REQUIRED )
include( GoogleTest )

include_directories( ${CMAKE_SOURCE_DIR}/include )
include_directories( ${CMAKE_SOURCE_DIR}/src )

set( TEST ${PROJECT_NAME}_test )
add_executable( ${TEST}
    main.cpp
    io/TEST_read_image.cpp
    io/drivers/gdal/TEST_GDAL_Codes.cpp
    io/drivers/gdal/TEST_GDAL_Utilities.cpp
    io/drivers/gdal/TEST_Read_Image_Resource_Disk_GDAL_Factory.cpp
)

target_link_libraries( ${TEST} PRIVATE
    GTest::gtest
    ${PROJECT_NAME}
)

#gtest_discover_tests( ${TEST} )

#  Copy Unit-Test Data
file( COPY ${CMAKE_SOURCE_DIR}/data/unit-test-data/images
      DESTINATION ${CMAKE_BINARY_DIR}/data )
