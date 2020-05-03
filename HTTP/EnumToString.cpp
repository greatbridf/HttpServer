//
// Created by David Mike on 2020/5/3.
//

#include "Base.hpp"

namespace greatbridf
{
    const char* toString(HTTPRequestType obj)
    {
        switch (obj)
        {
        case HTTPRequestType::GET:
            return "GET";
        case HTTPRequestType::POST:
            return "POST";
        default:
            return nullptr;
        }
    }
    const char* toString(HTTPVersion obj)
    {
        switch (obj)
        {
        case HTTPVersion::ONE:
            return "HTTP/1.1";
        case HTTPVersion::TWO:
            return "HTTP/2";
        default:
            return nullptr;
        }
    }
}
