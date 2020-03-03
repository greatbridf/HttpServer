//
// Created by David Mike on 2020/3/2.
//

#ifndef _EXITEXCEPTION_HPP_
#define _EXITEXCEPTION_HPP_

#include <utils/Foundation/Exceptions/Exception.hpp>

namespace greatbridf
{
    enum ExitCode
    {
        Normal = 0,
        BadArgs = 1,
        AlreadyRunning = 2,
        PermissionDenied = 3,
        NotRunning = 4,
    };
    class ExitException : public Exception
    {
     public:
        explicit ExitException(ExitCode _code);
        ExitCode cCode() const;
        int code() const;
     private:
        ExitCode __code;
    };
}

#endif //_EXITEXCEPTION_HPP_
