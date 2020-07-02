//
// Created by David Mike on 2020/2/29.
//

#ifndef _HTTPRESPONSECODES_HPP_
#define _HTTPRESPONSECODES_HPP_

#include <map>
#include <string>

namespace greatbridf::Static
{
    const std::map<int, std::string>& httpResponseCodes();

    constexpr unsigned int KEEP_ALIVE_DEFAULT_TIMEOUT = 5; // seconds
}

#endif //_HTTPRESPONSECODES_HPP_
