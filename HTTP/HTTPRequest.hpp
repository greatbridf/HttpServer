#pragma once

#include <string>
#include <sstream>
#include <map>

#include <utils/Exception.hpp>
#include "Base.hpp"

namespace greatbridf {

  const static std::string NULL_STRING = "";

  class HTTPRequest {
    public:

      explicit HTTPRequest(std::string& req);
      HTTPRequest();

      const std::string& getHeader(const char* key) const;
      const std::string& getQueryPath() const;
      HTTPRequestType getRequestType() const;
      HTTPVersion getHTTPVersion() const;

      const std::string& getRequestBody() const;

    private:
      HTTPRequestType type;
      HTTPVersion version;
      std::string path;

      std::string body;

      std::map<std::string, std::string> headers;

      void parseRequestHead(const std::string& req);
  };

}