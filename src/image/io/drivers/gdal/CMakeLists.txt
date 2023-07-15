#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    7/14/2023

include_directories( ${CMAKE_SOURCE_DIR}/include/terminus/image/io/drivers/gdal )

add_library( TERMINUS_IMAGE_IO_DRIVERS_GDAL OBJECT
             GDAL_Disk_Image_Impl.cpp
             GDAL_Disk_Image_Impl.hpp
             GDAL_Utilities.cpp
             GDAL_Utilities.hpp
             Read_Image_Resource_Disk_GDAL.cpp
             Read_Image_Resource_Disk_GDAL_Factory.cpp
)
