//
// Created by David Mike on 2020/5/1.
//

#include "PostHandler.hpp"

#include <utils/Foundation/StreamIOHelper.hpp>

namespace greatbridf
{
    PostHandler::~PostHandler() = default;

    bool PostHandler::isSuitable(HTTPRequest& request)
    {
        return request.getRequestType() == HTTPRequestType::POST;
    }

    IHTTPHandler::HandleResult PostHandler::handle(HTTPRequest& request, std::iostream& stream, HTTPResponse& response)
    {
        response.setResponseCode(200);

        auto length = request.bodySize();
        if (length > 0)
        {
            response.setHeader("Content-Length", length);
            stream << response;
            redirectStream(stream, stream, length);
        }
        else
        {
            stream << response << std::flush;
        }
        return IHTTPHandler::HandleResult::SUCCESS;
    }
    PostPlugin::PostPlugin()
        : IPlugin("http_request_handler_post", PluginType::Handler)
    {
        this->impl = (void*)new PostHandler();
    }
    PostPlugin::~PostPlugin()
    {
        delete (PostHandler*)this->impl;
    }
}