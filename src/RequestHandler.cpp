//
// Created by David Mike on 2020/7/13.
//
#include <Application.h>

using namespace greatbridf;

// TODO: a better way instead of global objects
extern greatbridf::Application* app;

RequestHandler::RequestHandler(std::unique_ptr<Socket> _socket,
    PluginManager& _manager)
    : socket(std::move(_socket)), manager(_manager)
{
}

void RequestHandler::run()
{
    try
    {
        IO::log("Connection from " + socket->getIP() + ':' + std::to_string(socket->getPort()));
        SocketBuffer buffer(*socket);
        std::iostream stream(&buffer);

        HTTPRequest request;
        bool keep_alive = false;
        socket->setTimeout(Static::KEEP_ALIVE_DEFAULT_TIMEOUT);
        while (stream >> request)
        {
            HTTPResponse response;
            if (request.headers().get("Connection") == "keep-alive")
            {
                response.headers().set("Keep-Alive", "timeout=" + std::to_string(socket->getTimeout()));
                keep_alive = true;
            }
            else
            {
                response.headers().set("Connection", "close");
                keep_alive = false;
            }

            bool handled = false;
            for (const auto& item : this->manager.getPlugins())
            {
                if (item->getType() != IPlugin::PluginType::Handler) continue;
                auto handler = item->handlerType();
                if (handler->isSuitable(request))
                {
                    handler->handle(request, stream, response, (void*)&app->configs().sites()[0]);
                    handled = true;
                    break;
                }
            }

            if (!handled)
            {
                response.setResponseCode(400);
                stream << response << std::flush;
            }

            if (!keep_alive) break;
        }

        stream.setstate(std::ios::eofbit);
        socket->close();
    }
    catch (Exception& e)
    {
        IO::log("Error encountered", std::cerr);
        IO::log(e.what(), std::cerr);
    }
}

