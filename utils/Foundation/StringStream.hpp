//
// Created by David Mike on 2020/5/3.
//

#ifndef _STRINGSTREAM_HPP_
#define _STRINGSTREAM_HPP_

#include <string>

namespace greatbridf
{
    class OStringStream
    {
     public:
        explicit OStringStream();
        explicit OStringStream(const std::string& str);
        explicit OStringStream(std::string&& str);

        OStringStream& operator<<(const std::string& str);
        std::string str() const;

     private:
        std::string _str = "";
    };
}

#endif //_STRINGSTREAM_HPP_
