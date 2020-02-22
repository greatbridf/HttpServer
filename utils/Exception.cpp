#include "Exception.hpp"

namespace greatbridf {

  Exception::Exception(const char* msg) {
    this->msg = msg;
  }

  const char* Exception::what() const throw() {
    return this->msg.c_str();
  }

}