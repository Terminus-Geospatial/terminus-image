/**
 * @file    Detector_OCV_Base.cpp
 * @author  Marvin Smith
 * @date    7/30/2023
*/
#include "Detector_OCV_Base.hpp"

namespace tmns::feature::ocv {

/*********************************/
/*          Constructor          */
/*********************************/
Detector_OCV_Base::Detector_OCV_Base( Detector_Config_Base::ptr_t config )
  : Detector_Base( config ),
    m_config( config )
{
}

} // End of tmns::feature::ocv namespace