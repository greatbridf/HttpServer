#include "HTTPRequest.hpp"

namespace greatbridf  {

  HTTPRequest::HTTPRequest(): type(HTTPRequestType::NONE), version(HTTPVersion::NONE) {}

  const std::map<std::string, std::string>& HTTPRequest::getHeaders() const {
    return this->headers;
  }

  const std::string& HTTPRequest::getHeader(const char* key) const {
    return this->headers.find(key) != this->headers.end() ? this->headers.at(key) : NULL_STRING;
  }

  const std::string& HTTPRequest::getQueryPath() const {
    return this->path;
  }

  HTTPRequestType HTTPRequest::getRequestType() const {
    return this->type;
  }

  HTTPVersion HTTPRequest::getHTTPVersion() const {
    return this->version;
  }

  std::istream& operator>>(std::istream &is, HTTPRequest &request) {
    std::string tmp;

    // parse request type
    is >> tmp;
    if (tmp == "GET") request.type = HTTPRequestType::GET;
    else if (tmp == "POST") request.type = HTTPRequestType::POST;
    else throw Exception("Unexpected query type");

    // parse request path
    is >> request.path;

    // parse http version
    is >> tmp;
    if (tmp == "HTTP/1.1") request.version = HTTPVersion::ONE;
    else if (tmp == "HTTP/2") request.version = HTTPVersion::TWO;
    else throw Exception("unexpected http version");

    std::string key, value;

    // parse request head
    is.ignore(2);

    while (is.good() and is.peek() != '\r') {
      std::getline(is, key, ':');
      if (is.peek() == ' ') is.ignore();
      std::getline(is, value, '\r');
      is.ignore();

      request.headers.insert(std::make_pair(key, value));
    }
    is.ignore(2);

    return is;
  }

  size_t HTTPRequest::bodySize() const {
    auto str = this->getHeader("Content-Length");
    if (str.empty()) {
      return -1;
    }
    return std::stoi(str);
  }

}