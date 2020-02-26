//
// Created by David Mike on 2020/2/26.
//

#ifndef _POSTHANDLER_HPP_
#define _POSTHANDLER_HPP_

#include <HTTP/HTTPRequest.hpp>
#include <HTTP/HTTPResponse.hpp>
#include <utils/Foundation/StreamIOHelper.hpp>

namespace greatbridf
{
    namespace Handler
    {
        void POST(HTTPRequest& request, std::iostream& stream);
    }
}

#endif //_POSTHANDLER_HPP_
