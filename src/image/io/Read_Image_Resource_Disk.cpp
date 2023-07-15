/**
 * @file    Read_Image_Resource_Disk.cpp
 * @author  Marvin Smith
 * @date    7/14/2023
*/
#include "Read_Image_Resource_Disk.hpp"

namespace tmns::image::io {

/****************************************/
/*          Get the format info         */
/****************************************/
Image_Format Read_Image_Resource_Disk::format() const
{
    return m_format;
}

/************************************/
/*          Get the pathname        */
/************************************/
std::filesystem::path Read_Image_Resource_Disk::pathname() const
{
    return m_pathname;
}

} // end of tmns::image::io namespace