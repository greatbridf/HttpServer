//
// Created by David Mike on 2020/2/25.
//

#include <HTTP/HTTPResponse.hpp>

namespace greatbridf
{

    HTTPResponse::HTTPResponse(unsigned int code, HTTPVersion version)
        : head(code, version)
    {
        this->_headers.set("Content-Type", "text/html; charset=UTF-8");
        this->_headers.set(("Content-Length"), "0");
        this->_headers.set("Connection", "keep-alive");
    }

    std::string HTTPResponse::toString() const
    {
        std::ostringstream os;

        os << this->head;
        for (auto& item : this->_headers.raw())
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
    HTTPHeaders& HTTPResponse::headers()
    {
        return this->_headers;
    }
    std::istream& operator>>(std::istream& is, HTTPResponse& response)
    {
        is >> response.head;
        is >> response._headers;
        return is;
    }
}
