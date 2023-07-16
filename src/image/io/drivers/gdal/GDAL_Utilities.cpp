/**
 * @file    GDAL_Utilities.cpp
 * @author  Marvin Smith
 * @date    7/15/2023
*/
#include "GDAL_Utilities.hpp"

// External Terminus Libraries
#include <terminus/log/Logger.hpp>

// Terminus Libraries
#include "GDAL_Codes.hpp"

// Boost Libraries
#include <boost/algorithm/string/replace.hpp>


namespace tmns::image::io::gdal {

static tmns::log::Logger g_gdal_logger("tmns::imageio::drivers::gdal");
/****************************************/
/*          Get the GDAL Logger         */
/****************************************/
tmns::log::Logger& get_master_gdal_logger()
{
    return g_gdal_logger;
}

/****************************************/
/*          GDAL Error Handler          */
/****************************************/
static void CPL_STDCALL GDAL_Error_Handler( CPLErr      eErrClass,
                                            int         nError,
                                            const char* pszErrorMsg )
{
    boost::log::trivial::severity_level lvl;
    auto& logger = get_master_gdal_logger();

    switch(eErrClass)
    {
        case CE_Debug:
        case CE_Warning:
            lvl = boost::log::trivial::severity_level::warning;
            break;
        default:
            lvl = boost::log::trivial::severity_level::error;
            break;
    }

    std::string message;
    if( pszErrorMsg )
    {
        message = pszErrorMsg;
    }
    boost::replace_all(message, "\n", " ");

    if ( eErrClass == CE_Fatal )
    {
        logger.fatal( "GDAL: ", message, " (code = ", nError, ")" );
        outcome::panic( error::ErrorCode::FILE_IO_ERROR,
                        "GDAL: ", message, " (code = ", nError, ")" );
    }
}

/************************************/
/*          Initialize GDAL         */
/************************************/
ImageResult<void> Initialize_GDAL()
{
    CPLPushErrorHandler( GDAL_Error_Handler );
    // If we run out of handles, GDAL errors out. If you have more than 400
    // open, you probably have a bug.
    CPLSetConfigOption("GDAL_MAX_DATASET_POOL_SIZE", "400");
    GDALAllRegister();

    return outcome::ok();
}

/********************************************/
/*          Get the master GDAL mutex       */
/********************************************/
static std::mutex g_gdal_mtx;
std::mutex& get_master_gdal_mutex()
{
    return g_gdal_mtx;
}

/****************************************************************/
/*      Method for destrying GDAL even if dataset is null       */
/****************************************************************/
void GDAL_Deleter_Null_Okay( GDALDatasetH dataset )
{
    if( dataset )
    {
        ::GDALClose( dataset );
    }
}

/**************************************************************/
/*       Compare the set of color codes against the LUT       */
/**************************************************************/
ImageResult<Pixel_Format_Enum> gdal_driver_to_pixel_type( const std::vector<std::tuple<std::vector<int>,Pixel_Format_Enum>>& reference_lut,
                                                          const std::vector<int>&                                            channel_codes )
{
    for( const auto& ref_tup : reference_lut )
    {
        if( std::get<0>( ref_tup ) == channel_codes )
        {
            return outcome::ok<Pixel_Format_Enum>( std::get<1>( ref_tup ) );
        }
    }
    return outcome::fail( error::ErrorCode::NOT_FOUND,
                          "No matching color code found for color set: ",
                          ToLogString( channel_codes ) );
}


} // end of tmns::image::io::gdal namespace