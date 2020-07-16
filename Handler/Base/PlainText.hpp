//
// Created by David Mike on 2020/7/16
//

#ifndef _HANDLER_PLAINTEXT_HPP_
#define _HANDLER_PLAINTEXT_HPP_

#include <Utils/Foundation/Plugin/IPlugin.hpp>

namespace greatbridf
{
    class PlainTextHandler : public IHTTPHandler
    {
     public:
        bool isSuitable(HTTPRequest& request) override;
        HandleResult handle(HTTPRequest& request, std::iostream& stream, HTTPResponse& response, void* data) override;
    };
}

__GREATBRIDF_DEFINE_PLUGIN_(PlainText);

#endif
