//
// Created by David Mike on 2020/2/25.
//

#ifndef HTTPPARSER_SERIALIZABLE_HPP
#define HTTPPARSER_SERIALIZABLE_HPP

#include <string>
#include <ostream>

namespace greatbridf {

  class Serializable {
  public:
    virtual std::string toString() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Serializable& obj) {
      os << obj.toString();
      return os;
    }

  };

}

#endif //HTTPPARSER_SERIALIZABLE_HPP
