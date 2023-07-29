/**
 * @file    Options.hpp
 * @author  Marvin Smith
 * @date    7/28/2023
*/
#pragma once

// Terminus Libraries
#include <terminus/log/configure.hpp>

// C++ Libraries
#include <sstream>

class Options
{
    public:

        /**
         * Parse the command-line options
        */
        static Options parse_command_line( int   argc,
                                           char* argv[],
                                           char* envp[] );

        /**
         * Get the Logging Stream Config
        */
        std::string get_log_config() const;

        /**
         * Print Usage Instructions
        */
        std::string usage() const;

    private:

        /// Program Name
        std::filesystem::path m_app_name;

        /// Logging Configuration
        std::string m_log_config;

        /// Log Severity
        std::string m_log_severity { "info" };

}; // End of options class