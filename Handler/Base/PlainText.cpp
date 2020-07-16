//
// Created by David Mike on 2020/7/16
//

#include "PlainText.hpp"
#include <src/Configurations.hpp>

namespace greatbridf
{
    bool PlainTextHandler::isSuitable(HTTPRequest& _)
    {
        return true;
    }

    IHTTPHandler::HandleResult PlainTextHandler::handle(HTTPRequest& req, std::iostream& stream, HTTPResponse& resp, void* data)
    {
        auto site = (Site*)data;

        auto& size = req.headers().get("Content-Length");
        if (!size.empty())
        {
            stream.ignore(std::stoi(size));
        }

        resp.setResponseCode(200);
        resp.headers().set("Content-Length", site->path.size());
        resp.headers().set("Content-Type", "text/html");

        stream << resp << site->path << std::flush;
        return HandleResult::SUCCESS;
    }

    PlainText::PlainText()
        : IPlugin("http_request_handler_plain_text", PluginType::Handler)
    {
        this->impl = (void*) new PlainTextHandler();
    }

    PlainText::~PlainText()
    {
        delete (PlainTextHandler*)this->impl;
    }
}
