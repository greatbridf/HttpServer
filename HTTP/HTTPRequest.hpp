#pragma once

#include <string>
#include <sstream>
#include <map>

#include <utils/Exception.hpp>
#include "Base.hpp"

namespace greatbridf {

  const static std::string NULL_STRING;

  class HTTPRequest {
    public:

      HTTPRequest();

      const std::string& getHeader(const char* key) const;
      const std::map<std::string, std::string>& getHeaders() const;
      const std::string& getQueryPath() const;
      HTTPRequestType getRequestType() const;
      HTTPVersion getHTTPVersion() const;

      size_t bodySize() const;

      friend std::istream& operator>>(std::istream& is, HTTPRequest& request);

    private:
      HTTPRequestType type;
      HTTPVersion version;
      std::string path;

      std::map<std::string, std::string> headers;
  };

}