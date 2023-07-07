#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    7/7/2023
#

add_executable( warpcore_tests
                    io/tests/TEST_ImageIO.cpp )

target_link_libraries( warpcore_tests
                       GTest::gtest_main )

gtest_discover_tests( warpcore_tests )
