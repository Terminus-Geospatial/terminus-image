/**
 * @file    Options.cpp
 * @author  Marvin Smith
 * @date    7/28/2023
*/
#include "Options.hpp"

// Boost Libraries
#include <boost/algorithm/string.hpp>

// C++ Libraries
#include <deque>

/****************************************************/
/*          Parse all Command-Line Options          */
/****************************************************/
Options Options::parse_command_line( int argc,
                                     char* argv[],
                                     char* envp[] )
{
    Options options;
    options.m_app_name = argv[0];

    // Create list of arguments
    std::deque<std::string> args;
    for( int i = 1; i < argc; i++ )
    {
        args.emplace_back( argv[i] );
    }

    // Parse Command-Line Arguments
    std::string arg;
    while( !args.empty() )
    {
        arg = args.front();
        args.pop_front();

        // Check if help flag provided
        if( arg == "-h" || arg == "--help" )
        {
            std::cerr << options.usage() << std::flush;
            std::exit(1);
        }

        // Check verbose
        if( arg == "-v" )
        {
            options.m_log_severity = "debug";
        }
        if( arg == "-vv" )
        {
            options.m_log_severity = "trace";
        }
    }


    // Setup the logging config
    options.m_log_config = R"(
                [Core]
                Filter="%Severity% >= __LEVEL__"

                [Sinks.Console]
                Destination=Console
                Format="[%TimeStamp%] %Severity(align=true, brackets=true)%  (%Scope%) %Message%"
            )";

    boost::replace_all( options.m_log_config,
                        "__LEVEL__",
                        options.m_log_severity );

    return options;
}

/****************************************/
/*          Get the log config          */
/****************************************/
std::string Options::get_log_config() const
{
    return m_log_config;
}

/********************************************/
/*          Print Usage Instructions        */
/********************************************/
std::string Options::usage() const
{
    std::stringstream sout;
    sout << "usage: " << m_app_name.filename() << " [optional flags]" << std::endl;
    sout << std::endl;
    sout << " -v  : Log with debug logging." << std::endl;
    sout << " -vv : Log with trace logging." << std::endl;

    return sout.str();
}
