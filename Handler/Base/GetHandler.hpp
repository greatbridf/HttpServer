//
// Created by David Mike on 2020/5/1.
//

#ifndef _GETHANDLER_HPP_
#define _GETHANDLER_HPP_

#include <Utils/Foundation/Plugin/IHTTPHandler.hpp>
#include <Utils/Foundation/Plugin/IPlugin.hpp>

namespace greatbridf
{
    class GetHandler : public IHTTPHandler
    {
     public:
        ~GetHandler() override;
        bool isSuitable(HTTPRequest& request) override;
        HandleResult handle(HTTPRequest& request, std::iostream& stream, HTTPResponse& response, void* data) override;
    };

    class Plugin : public IPlugin
    {
     public:
        Plugin();
        ~Plugin() override;
    };
}

__GREATBRIDF_DEFINE_PLUGIN_(Plugin);

#endif //_GETHANDLER_HPP_
