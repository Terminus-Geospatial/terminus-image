/**
 * @file    Test_Environment.hpp
 * @author  Marvin Smith
 * @date    8/25/2023
*/
#pragma once

// Google Test Libraries
#include <gtest/gtest.h>

// Unit-Test Libraries
#include "Image_Datastore.hpp"

class Test_Environment : public ::testing::Environment
{
    public:

        Test_Environment() = default;
        
        virtual ~Test_Environment() = default;

        static void initialize( const std::optional<Image_Datastore>& image_datastore );

        static Image_Datastore const&  get_image_datastore();

    private:

        /**
         * Parameterized Constructor
        */
        Test_Environment( const std::optional<Image_Datastore>& image_datastore );

        Image_Datastore m_image_datastore;

}; // End of Test_Environment Class
