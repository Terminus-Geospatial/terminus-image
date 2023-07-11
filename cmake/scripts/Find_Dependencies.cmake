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

#--------------------------------#
#-      Terminus Libraries      -#
#--------------------------------#
find_package( terminus_log      REQUIRED )
find_package( terminus_outcome  REQUIRED )
