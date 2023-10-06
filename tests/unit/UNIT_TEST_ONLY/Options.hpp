/**
 * @file    Options.hpp
 * @author  Marvin Smith
 * @date    7/28/2023
*/
#pragma once

// Terminus Libraries
#include <terminus/log/configure.hpp>

// C++ Libraries
#include <optional>
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
         * Get the image cache
        */
        std::filesystem::path get_test_image_config_path() const;

        /**
         * Flag if we should use the GUI options
         */
        bool use_gui() const;

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

        /// Path pointing to test images
        std::filesystem::path m_test_image_config_path { "data/test_images.ini" };

        /// Flag if we should use a GUI
        bool m_use_gui { false };

}; // End of options class