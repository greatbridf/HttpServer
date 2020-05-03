//
// Created by David Mike on 2020/5/3.
//

#include "StringStream.hpp"

namespace greatbridf
{
    OStringStream::OStringStream()
        : _str(std::string())
    {
    }
    OStringStream::OStringStream(const std::string& str)
        : _str(std::string(str))
    {
    }
    OStringStream::OStringStream(std::string&& str)
        : _str(std::move(str))
    {
    }
    OStringStream& OStringStream::operator<<(const std::string& str)
    {
        this->_str.append(str);
        return *this;
    }
    std::string OStringStream::str() const
    {
        return this->_str;
    }
}
