//
// Created by David Mike on 2020/2/26.
//

#ifndef _STREAMIOHELPER_HPP_
#define _STREAMIOHELPER_HPP_

#include <iostream>

namespace greatbridf
{
    const static size_t BUF_SIZE = 512;

    void redirectStream(std::ostream& os, std::istream& is, size_t size);
}

#endif //_STREAMIOHELPER_HPP_
