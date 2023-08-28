/**
 * @file    Detector_Factory.hpp
 * @author  Marvin Smith
 * @date    8/6/2023
*/
#pragma once

// C++ Libraries
#include <map>
#include <memory>

namespace tmns::feature {

class Detector_Factory
{
    public:

        /// @brief Pointer Type
        typedef std::shared_ptr<Detector_Factory> ptr_t;

        /**
         * Create an empty instance of the factory
        */
        static Detector_Factory::ptr_t create_instance();

        /**
         * Create a default instance of the factory
         */
        static Detector_Factory::ptr_t create_default_instance();

    private:

        /// List of registered feature detectors
        std::map<std::string,Detector_Base_Generator::ptr_t> m_generators;

}; // End of Detector_Factory class

} // End of tmns::feature namespace