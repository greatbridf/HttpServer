//
// Created by David Mike on 2020/2/25.
//

#include "HTTPResponse.hpp"

namespace greatbridf {

  HTTPResponse::HTTPResponse(unsigned int code, HTTPVersion version, std::string _data)
      : head(code, version), data(std::move(_data)) {
    this->setContent(this->data);

    this->setHeader("Content-Type", "text/html; charset=UTF-8");
    this->setHeader("Connection", "close");
  };

  std::string HTTPResponse::toString() const {
    std::ostringstream os;

    os << this->head;
    for (auto& item : this->headers) {
      os << item.first << ": " << item.second << CRLF;
    }
    os << CRLF;

    os << data;

    return os.str();
  }

  void HTTPResponse::setContent(std::string _data) {
    this->headers["Content-Length"] = std::to_string(_data.size());
    this->data = std::move(_data);
  }

  void HTTPResponse::setHeader(const char *key, const char *value) {
    this->headers[key] = value;
  }

}