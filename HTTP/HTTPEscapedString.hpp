//
// Created by David Mike on 2020/2/27.
//

#ifndef _HTTPESCAPEDSTRING_HPP_
#define _HTTPESCAPEDSTRING_HPP_

#include <istream>
#include <string>

namespace greatbridf
{
    class HTTPEscapedString : public std::string
    {
        friend std::istream& operator>>(std::istream& is, HTTPEscapedString& str);
    };
}

#endif //_HTTPESCAPEDSTRING_HPP_
