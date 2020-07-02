//
// Created by David Mike on 2020/5/1.
//

#ifndef _GETHANDLER_HPP_
#define _GETHANDLER_HPP_

#include <Handler/IHTTPHandler.hpp>
#include <Utils/Foundation/Plugin/IPlugin.hpp>

namespace greatbridf
{
    class GetHandler : public IHTTPHandler
    {
     public:
        ~GetHandler() override;
        bool isSuitable(HTTPRequest& request) override;
        HandleResult handle(HTTPRequest& request, std::iostream& stream, HTTPResponse& response) override;
    };

    class Plugin : public IPlugin
    {
     public:
        Plugin();
        ~Plugin() override;
    };
}

extern "C"
{
greatbridf::IPlugin* registerPlugin()
{
    return new greatbridf::Plugin();
}
}

#endif //_GETHANDLER_HPP_
