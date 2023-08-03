/**
 * @file    Detector_Base.cpp
 * @author  Marvin Smith
 * @date    7/30/2023
*/
#include "Detector_Base.hpp"

namespace tmns::feature {

/********************************/
/*          Constructor         */
/********************************/
Detector_Base::Detector_Base( Detector_Config_Base::ptr_t config )
 : m_config( config ),
   m_logger( config->logger_name() )
{
}

} // End of tmns::feature namespace