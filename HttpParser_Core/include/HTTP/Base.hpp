//
// Created by David Mike on 2020/2/25.
//

#ifndef HTTPPARSER_BASE_HPP
#define HTTPPARSER_BASE_HPP

#include <string>

namespace greatbridf
{
    const static char* CRLF = "\r\n";

    enum class HTTPRequestType
    {
        GET,
        POST,
        NONE,
    };

    enum class HTTPVersion
    {
        ONE,
        TWO,
        NONE,
    };

    const char* toString(HTTPRequestType obj);
    const char* toString(HTTPVersion obj);

    namespace Parse
    {
        HTTPRequestType RequestType(const std::string& str);
        HTTPVersion Version(const std::string& str);
    }
}

#endif //HTTPPARSER_BASE_HPP
