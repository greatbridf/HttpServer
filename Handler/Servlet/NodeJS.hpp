//
// Created by david on 7/16/20.
//

#ifndef _HANDLER_NODEJS_HPP_
#define _HANDLER_NODEJS_HPP_

#ifndef _GREATBRIDF_NODE_PATH
#define _GREATBRIDF_NODE_PATH "/usr/bin/node"
#endif

#include <Utils/Foundation/Plugin/IPlugin.hpp>

namespace greatbridf
{
    class NodeJSHandler : public IHTTPHandler
    {
     public:
        bool isSuitable(HTTPRequest& request) override;
        HandleResult handle(HTTPRequest& request, std::iostream& stream, HTTPResponse& response, void* data) override;
    };
}

__GREATBRIDF_DEFINE_PLUGIN_(NodeJS)

#endif //_HANDLER_NODEJS_HPP_
