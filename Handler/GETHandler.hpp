//
// Created by David Mike on 2020/2/26.
//

#ifndef _GETHANDLER_HPP_
#define _GETHANDLER_HPP_

#include <HTTP/HTTPRequest.hpp>
#include <HTTP/HTTPResponse.hpp>
#include <utils/Foundation/File.hpp>
#include <utils/Foundation/StreamIOHelper.hpp>
#include <utils/Foundation/BasicIO.hpp>

namespace greatbridf
{
    namespace Handler
    {
        void GET(HTTPRequest& request, std::iostream& stream);
    }
}

#endif //_GETHANDLER_HPP_
