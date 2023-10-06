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

class Test_Environment
{
    public:

        Test_Environment() = default;
        
        virtual ~Test_Environment() = default;

        static void initialize( const std::optional<Image_Datastore>& image_datastore,
                                bool                                  use_gui );

        static Image_Datastore const&  get_image_datastore();

        /**
         * Flag if the user wants to use the view APIs.
        */
        static bool use_gui();

    private:

        /**
         * Parameterized Constructor
        */
        Test_Environment( const std::optional<Image_Datastore>& image_datastore,
                          bool                                  use_gui );

        Image_Datastore m_image_datastore;

        bool m_use_gui;

}; // End of Test_Environment Class
