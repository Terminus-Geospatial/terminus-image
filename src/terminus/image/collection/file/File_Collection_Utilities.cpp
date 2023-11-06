/**
 * @file    File_Collection_Utilities.cpp
 * @author  Marvin Smith
 * @date    8/26/2023
 */
#include "File_Collection_Utilities.hpp"

// TOML++
#include <toml++/toml.h>

// Terminus Libraries
#include <terminus/log/utility.hpp>

namespace tmns::image::cx::file {

/****************************************/
/*          Parse and INI File          */
/****************************************/
ImageResult<void> parse_toml_collection_file( const std::filesystem::path&        input_path,
                                              std::vector<std::filesystem::path>& image_list )
{
    // Check if the input file exists
    if( !std::filesystem::exists( input_path ) )
    {
        return outcome::fail( core::error::ErrorCode::FILE_NOT_FOUND,
                              "Input path does not exist: ",
                              input_path );
    }

    toml::table tbl;
    try
    {
        tbl = toml::parse_file( input_path.native() );
        
        // Check if the imagery node exists
        auto images_node = tbl["collection"];
        if( !!images_node["image_list"] )
        {
            // Grab the image list
            auto list_node = tbl["image_list"];
            if( !!list_node )
            {
                // increment each element with visit()
                list_node.as_array()->for_each([&](auto&& el)
                {
                    std::string element = el.as_string()->get();
            
                    image_list.push_back( element );
                });
            }
        }

        if( !!images_node["images"] )
        {
            int image_id;
            std::string pathname;

            toml::table image_list_node = *images_node["images"].as_table();
            image_list_node.for_each([&]( const toml::key& key, 
                                          toml::table& image_node )
            {
                // Check if the key is a number
                try
                {
                    // Get the key
                    pathname = image_node["pathname"].as_string()->get();;
                    
                    std::cout << "image: " << key << ", path: " << pathname << std::endl;
                    image_list.push_back( pathname );
                    
                }
                catch ( std::exception& e )
                {

                }
            });
        }
    }
    catch (const toml::parse_error& err)
    {
        return outcome::fail( core::error::ErrorCode::PARSING_ERROR,
                              "Problem Parsing TOML File: ",
                              input_path, "What: ", err.what() );
    }

    return outcome::ok();
}

}