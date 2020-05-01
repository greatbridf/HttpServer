//
// Created by David Mike on 2020/5/1.
//

#include "GetHandler.hpp"

namespace greatbridf
{
    GetHandler::~GetHandler() = default;

    bool GetHandler::isSuitable(HTTPRequest& request)
    {
        return request.getRequestType() == HTTPRequestType::GET;
    }

    IHTTPHandler::HandleResult
    GetHandler::handle(HTTPRequest& request, std::iostream& stream, HTTPResponse& response)
    {
        response.setResponseCode(502);
        response.setHeader("Content-Type", "text/html; charset=utf-8");
        response.setHeader("Content-Length", "14");
        stream << response << std::flush;
        stream << "<h1>Error</h1>" << std::flush;
        return IHTTPHandler::HandleResult::SUCCESS;
    }
    Plugin::Plugin()
        : IPlugin("http_request_handler_get", PluginType::Handler)
    {
        this->impl = (void*)new GetHandler();
    }
    Plugin::~Plugin()
    {
        delete (GetHandler*)this->impl;
    };
}
