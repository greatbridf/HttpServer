//
// Created by David Mike on 2020/2/26.
//

#include "GETHandler.hpp"

namespace greatbridf
{
    namespace Handler
    {
        void GET(HTTPRequest& request, std::iostream& stream)
        {
            auto path = request.getQueryPath();
            if (path == "/")
            {
                path = "/index.html";
            }

            File file("." + path);
            if (!file.good())
            {
                stream << HTTPResponse(404) << std::flush;
                return;
            }

            HTTPResponse response(200, HTTPVersion::ONE);
            response.setHeader("Content-Length", file.fileSize());
            stream << response;
            redirectStream(stream, file, file.fileSize());
        }

        void POST(HTTPRequest& request, std::iostream& stream)
        {
            HTTPResponse response(200);

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
        }
    }
}
