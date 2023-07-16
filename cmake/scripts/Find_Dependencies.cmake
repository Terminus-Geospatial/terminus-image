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
set( Boost_USE_MULTITHREADED ON )
add_definitions( -DBOOST_ALL_DYN_LINK )
find_package( Boost REQUIRED
                COMPONENT
                    json
                    log
                    log_setup
                    system )
message( STATUS "${COLOR_BOLD}Boost_LIBRARIES: ${COLOR_RESET}${Boost_LIBRARIES}")

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
