#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    7/7/2023
#

find_package( GTest REQUIRED )

add_executable( warpcore_tests
                    io/TEST_ImageIO.cpp )

target_link_libraries( warpcore_tests
                       GTest::gtest_main )

#gtest_discover_tests( warpcore_tests )
