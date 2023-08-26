/**
 * @file    Test_Environment.cpp
 * @author  Marvin Smith
 * @date    8/25/2023
*/
#include "Test_Environment.hpp"

// Terminus Libraries
#include <terminus/log/utility.hpp>

// C++ Libraries
#include <memory>

static std::unique_ptr<Test_Environment> new_env;

/********************************/
/*          Initialize          */
/********************************/
void Test_Environment::initialize( const std::optional<Image_Datastore>& image_datastore )
{
    Image_Datastore output_img_ds;
    if( !image_datastore )
    {
        tmns::log::warn( "Image datastore not initialized." );
    }
    else
    {
        tmns::log::trace( "Initializing Test Environment" );
        output_img_ds = image_datastore.value();
    }
    
    
    new_env = std::unique_ptr<Test_Environment>( new Test_Environment( output_img_ds ) );
}

/*************************************/
/*      Get the Image Datastore      */
/*************************************/
Image_Datastore const& Test_Environment::get_image_datastore() 
{
    if( !new_env )
    {
        tmns::log::fatal( "Test_Environment not initialized." );
    }
    return new_env->m_image_datastore;
}

/********************************/
/*          Constructor         */
/********************************/
Test_Environment::Test_Environment( const std::optional<Image_Datastore>& image_datastore )
{
    if( image_datastore )
    {
        m_image_datastore = *image_datastore;
    }
}
