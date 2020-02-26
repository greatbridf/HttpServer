//
// Created by David Mike on 2020/2/26.
//

#include "POSTHandler.hpp"

namespace greatbridf
{
    namespace Handler
    {
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
