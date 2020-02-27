//
// Created by David Mike on 2020/2/27.
//

#include "HTTPEscapedString.hpp"

namespace greatbridf
{
    std::istream& operator>>(std::istream& is, HTTPEscapedString& str)
    {
        char c;
        int h;

        while ((c = is.peek()) == ' ') is.ignore();

        while ((c = is.get()) != ' ')
        {
            if (c == '%')
            {
                is >> std::hex >> h >> std::dec;
                str += static_cast<char>(h);
            }
            else
            {
                str += c;
            }
        }
        return is;
    }
}
