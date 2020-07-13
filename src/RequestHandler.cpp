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

bool is_site_suitable(const Site& site, const HTTPRequest& request)
{
    return ::std::regex_match(request.getQueryPath(), ::std::regex(site.rule));
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
            auto sites = app->configs().sites();
            auto plugins = manager.getPlugins();
            for (const auto& site : sites)
            {
                if (!is_site_suitable(site, request))
                {
                    continue;
                }
                for (const auto& plugin : plugins)
                {
                    if (!strcmp(plugin->getName(), site.handler.c_str()))
                    {
                        plugin->handlerType()->handle(request, stream, response, (void*)&site);
                        handled = true;
                        break;
                    }
                }
                if (handled) break;
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

