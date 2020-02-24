#pragma once

#include <string>
#include <sstream>
#include <map>

#include "../utils/Exception.hpp"

namespace greatbridf {

  const static std::string NULL_STRING = "";

  class HTTPRequest {
    public:
      enum class RequestType {
        GET,
        POST,
        NONE,
      };

      enum class HTTPVersion {
        ONE,
        TWO,
        NONE,
      };

      explicit HTTPRequest(std::string& req);
      HTTPRequest();

      const std::string& getHeader(const char* key) const;
      const std::string& getQueryPath() const;
      RequestType getRequestType() const;
      HTTPVersion getHTTPVersion() const;

      const std::string& getRequestBody() const;

    private:
      RequestType type;
      HTTPVersion version;
      std::string path;

      std::string body;

      std::map<std::string, std::string> headers;

      void parseRequestHead(const std::string& req);
  };

}