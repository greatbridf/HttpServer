//
// Created by David Mike on 2020/2/25.
//

#ifndef HTTPPARSER_HTTPRESPONSE_HPP
#define HTTPPARSER_HTTPRESPONSE_HPP


#include <map>

#include <utils/Foundation/Serializable.hpp>
#include <utils/Socket.hpp>
#include "HTTPResponseHead.hpp"


namespace greatbridf {

  class HTTPResponse : public Serializable {

  public:
    explicit HTTPResponse(unsigned int code = 400, HTTPVersion version = HTTPVersion::ONE);

    std::string toString() const override;
    friend Socket& operator<<(Socket& socket, const HTTPResponse& response);

    void setHeader(const char* key, const char* value);

  private:
    HTTPResponseHead head;
    std::map<std::string, std::string> headers;
  };
}

#endif //HTTPPARSER_HTTPRESPONSE_HPP
