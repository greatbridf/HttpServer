//
// Created by David Mike on 2020/2/25.
//

#ifndef HTTPPARSER_HTTPRESPONSEHEAD_HPP
#define HTTPPARSER_HTTPRESPONSEHEAD_HPP

#include <sstream>
#include <utils/Exception.hpp>
#include "Base.hpp"

namespace greatbridf
{

    class HTTPResponseHead : public Serializable
    {
     public:
        explicit HTTPResponseHead(unsigned int code)
            : code(code)
        {
        };
        explicit HTTPResponseHead(unsigned int code, HTTPVersion version)
            : code(code), version(version)
        {
        };

        std::string toString() const override
        {
            std::ostringstream os("");

            switch (this->version)
            {
            case HTTPVersion::NONE:
                throw Exception("Bad protocol version");

            case HTTPVersion::ONE:
                os << "HTTP/1.1 ";
                break;

            case HTTPVersion::TWO:
                os << "HTTP/2 ";
                break;
            }

            switch (this->code)
            {
            case 200:
                os << 200 << " OK" << CRLF;
                break;

            case 400:
                os << 400 << " Bad Request" << CRLF;
                break;

            case 404:
                os << 404 << " Not Found" << CRLF;
                break;

            default:
                os << 500 << " Internal Server Error" << CRLF;
                break;
            }

            return os.str();
        }

     private:
        unsigned int code;
        HTTPVersion version = HTTPVersion::ONE;

    };

}

#endif //HTTPPARSER_HTTPRESPONSEHEAD_HPP
