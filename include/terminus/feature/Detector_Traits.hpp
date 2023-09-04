/**
 * @file    Detector_Traits.hpp
 * @author  Marvin Smith
 * @date    9/2/2023
*/
#pragma once

// C++ Libraries
#include <type_traits>

namespace tmns::feature::trait {

template <typename DetectorT>
struct Has_Feature_Extractor : std::false_type {};


} // End of tmns::feature::trait namespace