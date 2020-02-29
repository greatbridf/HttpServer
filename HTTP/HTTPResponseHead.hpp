//
// Created by David Mike on 2020/2/25.
//

#ifndef HTTPPARSER_HTTPRESPONSEHEAD_HPP
#define HTTPPARSER_HTTPRESPONSEHEAD_HPP

#include <sstream>
#include <utils/Exception.hpp>
#include <Static/HTTPResponseCodes.hpp>
#include "Base.hpp"

namespace greatbridf
{

    class HTTPResponseHead : public Serializable
    {
     public:
        unsigned int code;
        HTTPVersion version = HTTPVersion::ONE;

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

            auto& responseCodes = Static::httpResponseCodes();
            if (responseCodes.find(this->code) == responseCodes.end())
            {
                os << 500 << ' ' << responseCodes.at(500) << CRLF;
            }
            else
            {
                os << this->code << ' ' << responseCodes.at(this->code) << CRLF;
            }

            return os.str();
        }
    };

}

#endif //HTTPPARSER_HTTPRESPONSEHEAD_HPP
