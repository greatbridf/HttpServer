#include "HTTPRequest.hpp"

namespace greatbridf  {

  HTTPRequest::HTTPRequest(std::string& req): type(HTTPRequestType::NONE), version(HTTPVersion::NONE) {
    auto pos = req.find("\r\n\r\n");
    if (pos == std::string::npos) {
      throw Exception("Bad request");
    }

    this->parseRequestHead(req.substr(0, pos));

    this->body = req.substr(pos+4, req.size()-1);
  }

  HTTPRequest::HTTPRequest(): type(HTTPRequestType::NONE), version(HTTPVersion::NONE) {}

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

  const std::string& HTTPRequest::getRequestBody() const {
      return this->body;
  }

  void HTTPRequest::parseRequestHead(const std::string &req) {
    std::istringstream ss(req);
    std::string type, version;
    ss >> type >> this->path >> version;

    if (type == "GET") this->type = HTTPRequestType::GET;
    else if (type == "POST") this->type = HTTPRequestType::POST;
    else throw Exception("unexpected query type");

    if (version == "HTTP/1.1") this->version = HTTPVersion::ONE;
    else if (version == "HTTP/2") this->version = HTTPVersion::TWO;
    else throw Exception("unexpected http version");

    // parse headers
    char c = 0x00;
    std::string key, value;
    while (ss.good()) {
      c = ss.peek();
      if (c == '\r' or c == '\n' or c == EOF) {
        ss.ignore(1);
        continue;
      }
      std::getline(ss, key, ':');
      if (ss.peek() == ' ') ss.ignore(1);
      std::getline(ss, value, '\r');
      this->headers.insert(std::make_pair(key, value));
    }
  }

}