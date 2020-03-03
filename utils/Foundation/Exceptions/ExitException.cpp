//
// Created by David Mike on 2020/3/2.
//

#include "ExitException.hpp"

namespace greatbridf
{
    ExitException::ExitException(ExitCode _code)
        : Exception(""), __code(_code)
    {
    }
    ExitCode ExitException::cCode() const
    {
        return __code;
    }
    int ExitException::code() const
    {
        return static_cast<int>(cCode());
    }
}
