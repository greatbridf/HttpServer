//
// Created by David Mike on 2020/2/26.
//

#include "StreamIOHelper.hpp"

namespace greatbridf
{
    void redirectStream(std::ostream& os, std::istream& is, size_t size)
    {
        redirectStream(os, is, 0, size);
    }
    void redirectStream(std::ostream& os, std::istream& is, size_t start, size_t size)
    {
        char* buf = (char*)::malloc(sizeof(char) * BUF_SIZE);
        size_t fin = 0;
        size_t pos = -1;

        if (start != 0)
        {
            pos = is.tellg();
            is.seekg(start, std::ios::beg);
        }

        while (is.good() and fin < size)
        {
            size_t n = std::min(BUF_SIZE, size - fin);
            is.read(buf, n);
            os.write(buf, n);

            fin += n;
        }

        os.flush();
        ::free(buf);

        if (start != 0)
        {
            is.seekg(pos, std::ios::beg);
        }
    }
}
