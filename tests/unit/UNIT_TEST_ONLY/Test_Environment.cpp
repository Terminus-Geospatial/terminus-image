/**
 * @file    Test_Environment.cpp
 * @author  Marvin Smith
 * @date    8/25/2023
*/
#include "Test_Environment.hpp"

static Test_Environment new_env;

/********************************/
/*          Initialize          */
/********************************/
void Test_Environment::initialize( const std::optional<Image_Datastore>& image_datastore )
{
    new_env = Test_Environment( image_datastore );
}

/*************************************/
/*      Get the Image Datastore      */
/*************************************/
Image_Datastore const& Test_Environment::get_image_datastore() 
{
    return new_env.get_image_datastore();
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
