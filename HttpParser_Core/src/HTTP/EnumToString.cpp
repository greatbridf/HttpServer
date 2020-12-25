//
// Created by David Mike on 2020/5/3.
//

#include <HTTP/Base.hpp>
#include <string>
#include <Utils/Foundation/Exceptions/Exception.hpp>

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
    HTTPRequestType Parse::RequestType(const std::string& str)
    {
        if (str == "GET")
        {
            return HTTPRequestType::GET;
        }
        else if (str == "POST")
        {
            return HTTPRequestType::POST;
        }
        else
        {
            throw Exception("unexpected request type");
        }
    }
    HTTPVersion Parse::Version(const std::string& str)
    {
        if (str == "HTTP/1.1" or str == "HTTP/1.0")
        {
            return HTTPVersion::ONE;
        }
        else if (str == "HTTP/2")
        {
            return HTTPVersion::TWO;
        }
        else
        {
            throw Exception("unexpected protocol version");
        }
    }
}
