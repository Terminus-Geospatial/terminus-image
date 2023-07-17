/**
 * @file    Read_Image_Resource_Disk.cpp
 * @author  Marvin Smith
 * @date    7/14/2023
*/
#include "Read_Image_Resource_Disk.hpp"

namespace tmns::image::io {

// Initialize Static Variables
bool Read_Image_Resource_Disk::s_default_rescale = true;

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

/************************************/
/*          Constructor             */
/************************************/
Read_Image_Resource_Disk::Read_Image_Resource_Disk( const std::filesystem::path& pathname )
  : m_pathname( pathname ),
    m_rescale( s_default_rescale )
{
}


} // end of tmns::image::io namespace