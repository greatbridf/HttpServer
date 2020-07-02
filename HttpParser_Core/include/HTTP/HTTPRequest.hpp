#pragma once

#include <string>
#include <sstream>
#include <map>
#include <vector>

#include "../Utils/Foundation/Exceptions/Exception.hpp"
#include "../Utils/Foundation/Serializable.hpp"
#include "Base.hpp"
#include "HTTPEscapedString.hpp"
#include "HTTPHeaders.hpp"

namespace greatbridf
{

    const static std::string NULL_STRING;

    class HTTPRequest : public Serializable
    {
     public:

        HTTPRequest();

        /// Make a new request with default values
        HTTPRequest(HTTPRequestType _type, std::string&& _path, HTTPVersion _version);

        std::string toString() const override;

        const std::string& getQueryPath() const;
        std::vector<std::pair<size_t, size_t>> getRange() const;
        HTTPRequestType getRequestType() const;
        HTTPVersion getHTTPVersion() const;

        size_t bodySize() const;

        friend std::istream& operator>>(std::istream& is, HTTPRequest& request);

        HTTPHeaders& headers();

     protected:
        HTTPRequestType type;
        HTTPVersion version;
        HTTPEscapedString path;
        HTTPHeaders _headers;

        void clear();
    };

}