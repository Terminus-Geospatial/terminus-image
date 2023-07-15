/**
 * @file    Pixel_Base.hpp
 * @author  Marvin Smith
 * @date    7/11/2023
*/
#pragma once

namespace tmns::image {

template <typename DerivedT>
class Pixel_Base
{
    public:

        /// Methods to access derived type
        DerivedT      & impl()       { return static_cast<DerivedT      &>(*this); }
        DerivedT const& impl() const { return static_cast<DerivedT const&>(*this); }

        static consteval size_t channels() { return 0; }

}; // End of PixelBase Class

} // End of tmns::image namespace