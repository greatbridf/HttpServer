//
// Created by David Mike on 2020/2/26.
//

#ifndef _STREAMIOHELPER_HPP_
#define _STREAMIOHELPER_HPP_

#include <iostream>

namespace greatbridf
{
    const static size_t BUF_SIZE = 512;

    void redirectStream(std::ostream& os, std::istream& is, size_t size)
    {
        char* buf = (char*)::malloc(sizeof(char) * BUF_SIZE);
        size_t fin = 0;

        while (fin < size)
        {
            size_t n = std::min(BUF_SIZE, size - fin);
            is.read(buf, n);
            os.write(buf, n);

            fin += n;
        }

        os.flush();
        ::free(buf);
    }
}

#endif //_STREAMIOHELPER_HPP_
