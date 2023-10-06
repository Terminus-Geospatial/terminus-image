/**
 * @file    Image_Datastore.hpp
 * @author  Marvin Smith
 * @date    8/25/2023
*/
#pragma once

// C++ Libraries
#include <filesystem>
#include <map>
#include <optional>
#include <string>

class Image_Datastore
{
    public:

        Image_Datastore() = default;
        
        virtual ~Image_Datastore() = default;

        /**
         * Load the image datastore from disk
         */
        static std::optional<Image_Datastore> load( const std::filesystem::path& config_path );
        
        /**
         * Get the full path for the keyword provided. 
         * 
         * The config-file has keywords mapped to images.  Adjust to your needs.
         */
        std::optional<std::filesystem::path> get_path( const std::string& keyword ) const;
    
    private:

        /**
         * Build a datastore from the configuration file.
        */
        Image_Datastore( const std::map<std::string,std::filesystem::path>& image_list );

        /// List of keywords mapped to image files
        std::map<std::string,std::filesystem::path> m_image_list;

}; // End of Image_Datastore Class