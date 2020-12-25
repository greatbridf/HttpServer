//
// Created by david on 7/16/20.
//

#include "NodeJS.hpp"

#include <Utils/Foundation/PosixCall.hpp>
#include <Utils/Foundation/Plugin/Site.hpp>
#include <Utils/Foundation/BasicIO.hpp>

bool greatbridf::NodeJSHandler::isSuitable(HTTPRequest& request)
{
    return true;
}

greatbridf::IHTTPHandler::HandleResult
greatbridf::NodeJSHandler::handle(HTTPRequest& request, std::iostream& stream, HTTPResponse& response, void* data)
{
    auto* site = (greatbridf::Site*)data;

    auto size = request.headers().get("Content-Length");
    if (!size.empty())
    {
        stream.ignore(std::stoi(size));
    }

    ::std::string node_path = _GREATBRIDF_NODE_PATH;

    char* const args[] =
        {
            (char* const)node_path.c_str(),
            (char* const)site->path.c_str(),
            nullptr
        };

    exec_info info{ node_path.c_str(), args, nullptr };
    byte_array input_data{ nullptr, 0 };

    response.setResponseCode(200);
    response.headers().set("Transfer-Encoding", "chunked");
    response.headers().unset("Content-Length");
    response.headers().set("Content-Type", "text/plain");
    stream << response << std::flush;

    auto ret = pipe_exec(&info, &input_data, [&](byte_array* arr)
    {
        // TODO: write chuck function
        stream << ::std::hex << arr->size << ::std::dec << CRLF;
        stream.write((const char*)arr->arr, arr->size);
        stream << CRLF << std::flush;
    }, [](byte_array* arr)
    {
        IO::log("stderr data", ::std::cerr);
    });
    stream << 0 << CRLF << CRLF << std::flush;

    if (ret) return HandleResult::FAILURE;
    return HandleResult::SUCCESS;
}

greatbridf::NodeJS::NodeJS()
    : IPlugin("http_request_handler_nodejs", PluginType::Handler)
{
    this->impl = (void*)new NodeJSHandler();
}

greatbridf::NodeJS::~NodeJS()
{
    delete (NodeJSHandler*)this->impl;
}
