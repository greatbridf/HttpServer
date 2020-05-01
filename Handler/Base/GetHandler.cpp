//
// Created by David Mike on 2020/5/1.
//

#include <utils/Foundation/File.hpp>
#include <utils/Foundation/StreamIOHelper.hpp>
#include "GetHandler.hpp"

namespace greatbridf
{
    void ServeStaticResource(std::ostream& stream, HTTPResponse& response, File& file)
    {
        response.setResponseCode(200);
        response.setHeader("Content-Length", file.fileSize());
        response.setHeader("Content-Type", file.getMimeType());
        stream << response << std::flush;
        redirectStream(stream, file, file.fileSize());
    }
    void ServeWithRange(std::ostream& stream, HTTPResponse& response, File& file, std::pair<size_t, size_t>& range)
    {
        if (range.second == -1)
        {
            range.second = file.fileSize() - 1;
        }
        auto size = range.second - range.first + 1;
//            std::ostringstream ss("");
//            ss << "bytes " << range.first << '-' << range.second << '/' << file.fileSize();
        std::string strRange("bytes ");
        strRange += std::to_string(range.first);
        strRange += '-';
        strRange += std::to_string(range.second);
        strRange += '/';
        strRange += std::to_string(file.fileSize());

        response.setResponseCode(206);
        response.setHeader("Content-Length", size);
        response.setHeader("Content-Range", strRange);
        stream << response << std::flush;
        redirectStream(stream, file, range.first, size);
    }

    GetHandler::~GetHandler() = default;

    bool GetHandler::isSuitable(HTTPRequest& request)
    {
        return request.getRequestType() == HTTPRequestType::GET;
    }

    IHTTPHandler::HandleResult
    GetHandler::handle(HTTPRequest& request, std::iostream& stream, HTTPResponse& response)
    {
        auto& path = request.getQueryPath();

        File file(std::filesystem::path("." + path));
        if (!file.good())
        {
            response.setResponseCode(404);
            response.setHeader("Content-Length", 0);
            response.setHeader("Content-Type", "text/plain");
            stream << response << std::flush;
            return IHTTPHandler::HandleResult::SUCCESS;
        }

        auto const&& mime = std::move(file.getMimeType());
        if (mime == "text/html" or mime == "application/x-javascript" or mime == "text/css")
        {
            ServeStaticResource(stream, response, file);
            return IHTTPHandler::HandleResult::SUCCESS;
        }
        response.setHeader("Accept-Range", "bytes");
        if (request.getHeader("Range").empty())
        {
            ServeStaticResource(stream, response, file);
            return IHTTPHandler::HandleResult::SUCCESS;
        }
        auto range = std::move(request.getRange());
        if (range.size() == 1)
        {
            ServeWithRange(stream, response, file, range.at(0));
        }
        else
        {
            response.setResponseCode(500);
            response.setHeader("Content-Length", 0);
            response.setHeader("Content-Type", "text/plain");
            stream << response << std::flush;
        }
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
