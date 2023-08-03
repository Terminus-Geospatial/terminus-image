/**
 * @file    Compound_Utilities.hpp
 * @author  Marvin Smith
 * @date    8/2/2023
*/
#pragma once

// Terminus Libraries
#include "compounds/Binary_Compound_Functor.hpp"
#include "compounds/Unary_Compound_Functor.hpp"
#include "Compound_Types.hpp"

namespace tmns::image {


template <typename FuncT,
          typename Arg1T,
          typename Arg2T = void>
struct Compound_Result
{
    typedef typename std::invoke_result_t<cmp::Binary_Compound_Functor<FuncT, Arg1T, Arg2T>(Arg1T,Arg2T)> type;
};

template <typename FunctorT,
          typename ArgT>
struct Compound_Result<FunctorT,ArgT,void>
{
    typedef std::invoke_result_t<cmp::Unary_Compound_Functor<FunctorT,ArgT>,ArgT> type;
};

} // End of tmns::image namespace