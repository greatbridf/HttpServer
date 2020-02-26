//
// Created by David Mike on 2020/2/25.
//

#ifndef HTTPPARSER_BASE_HPP
#define HTTPPARSER_BASE_HPP

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

}

#endif //HTTPPARSER_BASE_HPP
