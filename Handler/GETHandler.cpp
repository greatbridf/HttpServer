//
// Created by David Mike on 2020/2/26.
//

#include "GETHandler.hpp"

namespace greatbridf
{
    namespace Handler
    {
        void GET(HTTPRequest& request, std::iostream& stream, HTTPResponse& response)
        {
            auto path = request.getQueryPath();
            if (path == "/")
            {
                path = "/index.html";
            }

            File file("." + path);
            if (!file.good())
            {
                response.setResponseCode(404);
                stream << response << std::flush;
                return;
            }

            response.setResponseCode(200);
            response.setHeader("Content-Length", file.fileSize());
            response.setHeader("Content-Type", std::move(file.getMimeType()));
            stream << response;
            redirectStream(stream, file, file.fileSize());
        }

    }
}
