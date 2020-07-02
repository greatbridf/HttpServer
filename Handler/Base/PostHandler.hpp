//
// Created by David Mike on 2020/5/1.
//

#ifndef _POSTHANDLER_HPP_
#define _POSTHANDLER_HPP_

#include <Utils/Foundation/Plugin/IHTTPHandler.hpp>
#include <Utils/Foundation/Plugin/IPlugin.hpp>

namespace greatbridf
{
    class PostHandler : public IHTTPHandler
    {
     public:
        ~PostHandler() override;
        bool isSuitable(HTTPRequest& request) override;
        HandleResult handle(HTTPRequest& request, std::iostream& stream, HTTPResponse& response) override;
    };

    class PostPlugin : public IPlugin
    {
     public:
        PostPlugin();
        ~PostPlugin() override;
    };
}

extern "C"
{
greatbridf::IPlugin* registerPlugin()
{
    return new greatbridf::PostPlugin();
}
}

#endif //_POSTHANDLER_HPP_
