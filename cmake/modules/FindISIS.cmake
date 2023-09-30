
#   @file FindISIS.cmake
#
#   @brief The CMake Find script for USGS ISIS
#
#   @date Sept 14, 2023
#
set( ISIS_LIB_INSTALL_PATHS
    /Users/marvinsmith/miniconda3/envs/isis
)


IF( NOT ISIS_FOUND )

    # Use FIND_PATH here to allow the user to set the path to IGNORE
    # to disable ISIS support.
    FIND_PATH( ISIS_INCLUDE_DIRS 
                    Isis.h
                PATHS
                    ${ISIS_LIB_INSTALL_PATHS}/include/isis
            )

    FIND_LIBRARY(ISIS_LIBRARY
                    isis
                 PATH
                    ${ISIS_LIB_INSTALL_PATHS}/lib
                )

    message("ISIS_LIBRARY: ${ISIS_LIBRARY}")

    IF( ISIS_INCLUDE_DIRS )
        SET( ISIS_INCLUDE_FOUND )
    ENDIF()
    IF( ISIS_LIBRARY )
        SET( ISIS_LIBRARY_FOUND )
    ENDIF()
    IF( ISIS_INCLUDE_DIRS AND ISIS_LIBRARY )
        SET( ISIS_FOUND "YES" )
        SET( ISIS_LIBRARIES ${ISIS_LIBRARY})
    ENDIF()

ENDIF()