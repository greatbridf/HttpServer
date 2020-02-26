//
// Created by David Mike on 2020/2/25.
//

#include "HTTPResponse.hpp"

namespace greatbridf
{

    HTTPResponse::HTTPResponse(unsigned int code, HTTPVersion version)
        : head(code, version)
    {

        this->setHeader("Content-Type", "text/html; charset=UTF-8");
        this->setHeader(("Content-Length"), "0");
        this->setHeader("Connection", "keep-alive");
    }

    std::string HTTPResponse::toString() const
    {
        std::ostringstream os;

        os << this->head;
        for (auto& item : this->headers)
        {
            os << item.first << ": " << item.second << CRLF;
        }
        os << CRLF;

        return os.str();
    }
    void HTTPResponse::setResponseCode(unsigned int code)
    {
        head.code = code;
    }

}