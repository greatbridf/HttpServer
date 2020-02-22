#include "HTTPRequest.hpp"

namespace greatbridf  {

  HTTPRequest::HTTPRequest(std::string& req) {
    std::istringstream ss(req);
    std::string type, version;
    ss >> type >> this->path >> version;

    if (type == "GET") this->type = RequestType::GET;
    else if (type == "POST") this->type = RequestType::POST;
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

  const std::string& HTTPRequest::getHeader(std::string& key) const {
    return this->headers.at(key);
  }

  const std::string& HTTPRequest::getQueryPath() const {
    return this->path;
  }

  HTTPRequest::RequestType HTTPRequest::getRequestType() const {
    return this->type;
  }

  HTTPRequest::HTTPVersion HTTPRequest::getHTTPVersion() const {
    return this->version;
  }

}