/**
 * @file    main.cpp
 * @author  Marvin Smith
 * @date    7/17/2023
 */
#include <gtest/gtest.h>

// Terminus Libraries
#include <terminus/log/configure.hpp>
#include <terminus/log/utility.hpp>

// Unit-Test Libraries
#include "UNIT_TEST_ONLY/Options.hpp"

int main(int argc, char* argv[], char* envp[] )
{
    // Parse Command-Line Options
    auto options = Options::parse_command_line( argc, argv, envp );

    // Setup the Terminus Logger
    std::istringstream log_config { options.get_log_config() };
    if( !tmns::log::configure( log_config ) )
    {
        tmns::log::error( "Unable to configure logging. Using defaults." );
    }
    tmns::log::info( "Logger initialized" );

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

