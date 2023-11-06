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
        
        // Grab the image list
        auto images_node = tbl["collection"]["images"]["image_list"];

        // increment each element with visit()
        images_node.as_array()->for_each([&](auto&& el)
        {
            std::string element = el.as_string()->get();
            
            image_list.push_back( element );
        });

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