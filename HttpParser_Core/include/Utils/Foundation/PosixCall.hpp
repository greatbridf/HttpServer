//
// Created by david on 7/16/20.
//

#ifndef HTTPPARSER_POSIXCALL_HPP
#define HTTPPARSER_POSIXCALL_HPP

#include <functional>

#include "Types.hpp"

namespace greatbridf
{
    struct exec_info
    {
        const char* path;
        char* const* p_arg;
        char* const* p_env;
    };

    struct byte_array
    {
        byte* arr;
        size_t size;
    };

    int pipe_exec(exec_info* info, byte_array* input_data,
        const ::std::function<void(byte_array*)>& on_stdout,
        const ::std::function<void(byte_array*)>& on_stderr);
}

#endif //HTTPPARSER_POSIXCALL_HPP
