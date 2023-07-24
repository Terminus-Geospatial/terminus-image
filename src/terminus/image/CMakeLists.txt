#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    7/10/2023

#  Add include paths
include_directories( TERMINUS_IMAGE_PIXEL PRIVATE
                     ${Boost_INCLUDE_DIRS}
                     ${terminus_log_INCLUDE_DIRS}
                     ${terminus_math_INCLUDE_DIRS}
                     ${terminus_outcome_INCLUDE_DIRS}
                     ${GDAL_INCLUDE_DIRS}
)

#  Process all subdirectory objects
add_subdirectory( io )
add_subdirectory( pixel )
add_subdirectory( types )

