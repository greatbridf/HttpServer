//
// Created by David Mike on 2020/2/25.
//

#ifndef HTTPPARSER_HTTPRESPONSE_HPP
#define HTTPPARSER_HTTPRESPONSE_HPP

#include <map>
#include <string>

#include <utils/Foundation/Serializable.hpp>
#include "HTTPResponseHead.hpp"

namespace greatbridf
{

    class HTTPResponse : public Serializable
    {

     public:
        explicit HTTPResponse(unsigned int code = 400, HTTPVersion version = HTTPVersion::ONE);

        std::string toString() const override;

        void setResponseCode(unsigned int code);

        template<typename T>
        void setHeader(const char* key, T value)
        {
            this->headers[key] = std::to_string(value);
        }

     private:
        HTTPResponseHead head;
        std::map<std::string, std::string> headers;
    };

    template<>
    void HTTPResponse::setHeader<std::string>(const char* key, std::string value);

    template<>
    void HTTPResponse::setHeader<const char*>(const char* key, const char* value);
}

#endif //HTTPPARSER_HTTPRESPONSE_HPP
