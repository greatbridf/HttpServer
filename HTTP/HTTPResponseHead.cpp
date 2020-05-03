//
// Created by David Mike on 2020/5/3.
//
#include "HTTPResponseHead.hpp"

namespace greatbridf
{
    HTTPResponseHead::HTTPResponseHead(unsigned int code)
        : code(code)
    {
    }
    HTTPResponseHead::HTTPResponseHead(unsigned int code, HTTPVersion version)
        : code(code), version(version)
    {
    }

    std::string HTTPResponseHead::toString() const
    {
        std::ostringstream os("");

        auto res = greatbridf::toString(this->version);
        if (res)
        {
            os << greatbridf::toString(this->version) << " ";
        }
        else
        {
            throw Exception("bad protocol version");
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
    std::istream& operator>>(std::istream& is, HTTPResponseHead& head)
    {
        // http version
        std::string tmp;
        is >> tmp;
        head.version = Parse::Version(tmp);

        // http response code
        is >> tmp;
        int result = 0;
        result = atoi(tmp.c_str());
        if (!result)
        {
            throw Exception("unexpected response code");
        }
        head.code = result;

        // skip response message
        is >> tmp;

        // skip trailing CRLF
        is.ignore(2, '\n');

        return is;
    }
}
