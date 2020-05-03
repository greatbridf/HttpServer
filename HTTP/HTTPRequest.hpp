#pragma once

#include <string>
#include <sstream>
#include <map>
#include <vector>

#include <utils/Foundation/Exceptions/Exception.hpp>
#include <utils/Foundation/Serializable.hpp>
#include "Base.hpp"
#include "HTTPEscapedString.hpp"

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

        const std::string& getHeader(const char* key) const;
        const std::map<std::string, std::string>& getHeaders() const;

        /*!
         * Insert a header line into the headers list
         * @param key key
         * @param value value
         */
        void setHeader(const std::string& key, const std::string& value);

        const std::string& getQueryPath() const;
        std::vector<std::pair<size_t, size_t>> getRange() const;
        HTTPRequestType getRequestType() const;
        HTTPVersion getHTTPVersion() const;

        size_t bodySize() const;

        friend std::istream& operator>>(std::istream& is, HTTPRequest& request);

     protected:
        HTTPRequestType type;
        HTTPVersion version;
        HTTPEscapedString path;

        std::map<std::string, std::string> headers;

        void clear();
    };

}