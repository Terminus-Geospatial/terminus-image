/**
 * @file    main.cpp
 * @author  Marvin Smith
 * @date    7/17/2023
 */
#include <gtest/gtest.h>

#include <terminus/log/configure.hpp>

int main(int argc, char **argv)
{
    // Setup the Terminus Logger
    tmns::log::configure();

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

