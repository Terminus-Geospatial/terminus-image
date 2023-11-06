/**
 * @file    TEST_tomlplusplus.cpp
 * @author  Marvin Smith
 * @date    11/5/2023
*/
#include <gtest/gtest.h>

//  Thirdparty libraries
#include <toml++/toml.h>

// Terminus Libraries
#include <terminus/log/utility.hpp>

/****************************************/
/*      Test Simple Toml++ Features     */
/****************************************/
TEST( thirdparty_tomlplusplus, test_01 )
{
    // Collection path to load
    std::filesystem::path collection_path { "./data/collection/dummy-collection.toml" };

    // Check if the input file exists
    if( !std::filesystem::exists( collection_path ) )
    {
        tmns::log::error( "Input path does not exist: ",
                          collection_path );
    }
    ASSERT_TRUE( std::filesystem::exists( collection_path ) );

    toml::table tbl;
    try
    {
        tbl = toml::parse_file( collection_path.native() );
        std::cout << tbl << "\n";
    }
    catch (const toml::parse_error& err)
    {
        std::cerr << "Parsing failed:\n" << err << "\n";
        FAIL();
    }
        
    // Check if node exists
    ASSERT_TRUE( !!tbl["collection"] );
    ASSERT_FALSE( !!tbl["collection"]["dummy"] );
}
