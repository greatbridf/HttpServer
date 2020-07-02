//
// Created by David Mike on 2020/3/3.
//

#include <Utils/Foundation/File.hpp>

namespace greatbridf
{
    template<>
    bool InputFile::writable() const
    {
        return false;
    }
    template<>
    bool OutputFile::readable() const
    {
        return false;
    }
}
