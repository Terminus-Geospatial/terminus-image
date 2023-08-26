/**
 * @file    Image_Datastore.cpp
 * @author  Marvin Smith
 * @date    8/25/2023
*/
#include "Image_Datastore.hpp"

// Boost Libraries
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

/************************************/
/*          Load Images             */
/************************************/
std::optional<Image_Datastore> Image_Datastore::load( const std::filesystem::path& config_path )
{   
    // If config path doesn't exist, return nothing
    if( std::filesystem::exists( config_path ) )
    {
        return {};
    }

    std::map<std::string,std::filesystem::path> image_list;

    // Open the config path 
    if( std::filesystem::exists( config_path ) )
    {
        // Use boost 
        boost::property_tree::ptree pt;
        boost::property_tree::ini_parser::read_ini( config_path.native(), pt );

        for( boost::property_tree::ptree::iterator it = pt.begin(); it != pt.end(); it++ )
        {
            std::string key = it->first;
            std::string val = it->second.get_value<std::string>();

            image_list[key] = std::filesystem::path( val );
        }
    }

    // Create a new instance
    Image_Datastore output( image_list );

    return output;

}

/****************************************/
/*          Get requested path          */
/****************************************/
std::optional<std::filesystem::path> Image_Datastore::get_path( const std::string& key_name ) const
{
    if( m_image_list.find( key_name ) == m_image_list.end() )
    {
        return {};
    }
    else
    {
        return m_image_list.find( key_name )->second;
    }
}

/************************************/
/*          Constructor             */
/************************************/
Image_Datastore::Image_Datastore( const std::map<std::string,std::filesystem::path>& image_list )
   : m_image_list( image_list )
{
}