#pragma once

#include <exception>
#include <string>

namespace greatbridf {

  class Exception : public std::exception{
    public:
      Exception(const char* msg);

      const char* what() const throw() override;

    private:
      std::string msg;
  };

}