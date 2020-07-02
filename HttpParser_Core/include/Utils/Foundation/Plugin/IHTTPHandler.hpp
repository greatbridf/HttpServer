//
// Created by David Mike on 2020/5/1.
//

#ifndef _IHTTPHANDLER_HPP_
#define _IHTTPHANDLER_HPP_

#include "../../../HTTP/HTTPRequest.hpp"
#include "../../../HTTP/HTTPResponse.hpp"

namespace greatbridf
{
    class IHTTPHandler
    {
     public:
        enum class HandleResult
        {
            SUCCESS,
            FAILURE,
        };

        virtual ~IHTTPHandler() = default;
        virtual bool isSuitable(HTTPRequest& request) = 0;
        virtual HandleResult handle(HTTPRequest& request, std::iostream& stream, HTTPResponse& response) = 0;
    };
}

#endif //_IHTTPHANDLER_HPP_
