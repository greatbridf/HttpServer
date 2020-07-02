//
// Created by David Mike on 2020/2/25.
//

#ifndef HTTPPARSER_HTTPRESPONSEHEAD_HPP
#define HTTPPARSER_HTTPRESPONSEHEAD_HPP

#include <sstream>
#include "../Utils/Foundation/Exceptions/Exception.hpp"
#include "../Utils/Foundation/Serializable.hpp"
#include "Base.hpp"
#include "HTTPResponseCodes.hpp"

namespace greatbridf
{

    class HTTPResponseHead : public Serializable
    {
     public:
        unsigned int code;
        HTTPVersion version = HTTPVersion::ONE;

        explicit HTTPResponseHead(unsigned int code);

        explicit HTTPResponseHead(unsigned int code, HTTPVersion version);

        std::string toString() const override;

        friend std::istream& operator>>(std::istream& is, HTTPResponseHead& head);
    };

}

#endif //HTTPPARSER_HTTPRESPONSEHEAD_HPP
