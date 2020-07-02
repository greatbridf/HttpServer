//
// Created by David Mike on 2020/2/25.
//

#ifndef HTTPPARSER_HTTPRESPONSE_HPP
#define HTTPPARSER_HTTPRESPONSE_HPP

#include <map>
#include <string>

#include <Utils/Foundation/Serializable.hpp>
#include "HTTPResponseHead.hpp"
#include "HTTPHeaders.hpp"

namespace greatbridf
{

    class HTTPResponse : public Serializable
    {

     public:
        explicit HTTPResponse(unsigned int code = 400, HTTPVersion version = HTTPVersion::ONE);

        std::string toString() const override;

        void setResponseCode(unsigned int code);

        HTTPHeaders& headers();

        friend std::istream& operator>>(std::istream& is, HTTPResponse& response);

     private:
        HTTPResponseHead head;
        HTTPHeaders _headers;
    };
}

#endif //HTTPPARSER_HTTPRESPONSE_HPP
