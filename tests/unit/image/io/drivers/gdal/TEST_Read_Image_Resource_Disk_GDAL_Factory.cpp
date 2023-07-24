/**
 * @file    TEST_Read_Image_Resource_Disk_GDAL_Factory.cpp
 * @author  Marvin Smith
 * @date    7/16/2023
*/
#include <gtest/gtest.h>

// Terminus Libraries
#include <terminus/image/io/drivers/gdal/Read_Image_Resource_Disk_GDAL_Factory.hpp>


/********************************************************************/
/*          Test the method for checking if a file is valid         */
/********************************************************************/
TEST( Read_Image_Resource_Disk_GDAL_Factory, is_image_supported )
{
    using namespace tmns::image::io;

    auto factory = std::make_shared<gdal::Read_Image_Resource_Disk_GDAL_Factory>();

    ASSERT_TRUE( factory->is_image_supported( "./data/images/jpeg/lena.jpg" ) );
}