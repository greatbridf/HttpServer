//
// Created by David Mike on 2020/7/13.
//

#ifndef _TYPES_HPP_
#define _TYPES_HPP_

#include <sys/types.h>

namespace greatbridf
{
    typedef unsigned char byte;

    class NonCopyable
    {
     public:
        NonCopyable() = default;
        NonCopyable(const NonCopyable&) = delete;
        NonCopyable& operator=(const NonCopyable&) = delete;
    };

    class Interface : private NonCopyable
    {
     public:
        virtual ~Interface() = default;
    };
}

#endif //_TYPES_HPP_
