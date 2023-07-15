#    File:    Find_Packages.cmake
#    Author:  Marvin Smith
#    Date:    7/5/2023
#

#

#-------------------------#
#-      GoogleTest       -#
#-------------------------#
find_package( GTest REQUIRED )

#--------------------#
#-      Boost       -#
#--------------------#
find_package( Boost REQUIRED )

#--------------------#
#-      GDAL        -#
#--------------------#
find_package( GDAL CONFIG REQUIRED )
message( STATUS  "${COLOR_BOLD}GDAL_FOUND: ${COLOR_RESET} ${GDAL_FOUND}")

if( NOT DEFINED GDAL_INCLUDE_DIRS )
    set( GDAL_INCLUDE_DIRS "/usr/local/include" )
endif()
message( STATUS  "${COLOR_BOLD}GDAL_INCLUDE_DIRS:${COLOR_RESET}${GDAL_INCLUDE_DIRS}" )

#terminus_dump_cmake_variables()

#--------------------------------#
#-      Terminus Libraries      -#
#--------------------------------#
find_package( terminus_log      REQUIRED )
find_package( terminus_math     REQUIRED )
find_package( terminus_outcome  REQUIRED )
