#pragma once

#include <string>
#include <sstream>
#include <map>

#include "../utils/Exception.hpp"

namespace greatbridf {

  class HTTPRequest {
    public:
      enum class RequestType {
        GET,
        POST,
      };

      enum class HTTPVersion {
        ONE,
        TWO,
      };

      HTTPRequest(std::string& req);
      const std::string& getHeader(std::string& key) const;
      const std::string& getQueryPath() const;
      RequestType getRequestType() const;
      HTTPVersion getHTTPVersion() const;

    private:
      RequestType type;
      HTTPVersion version;
      std::string path;

      std::map<std::string, std::string> headers;
  };

}