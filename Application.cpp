#include "Application.h"
#include <csignal>

namespace greatbridf
{
    class Task : public ITask
    {
     private:
        std::unique_ptr<Socket> socket;
        PluginManager& manager;
     public:
        explicit Task(std::unique_ptr<Socket> _socket, PluginManager& _manager)
            : socket(std::move(_socket)), manager(_manager)
        {
        }

        void run() override
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
                            handler->handle(request, stream, response);
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
    };

    Application* app = nullptr;

    int Application::run()
    {
        app = this;
        signal(SIGINT, [](int)
        {
            IO::log("Closing...");
            app->ss->close();
        });
        signal(SIGTERM, [](int)
        {
            IO::log("Closing...");
            app->ss->close();
        });
        signal(SIGPIPE, SIG_IGN);
        auto port = this->args.hasOption("-p") ? this->args.getOption("-p") : "8080";
        this->ss = std::make_unique<ServerSocket>(Socket::SocketType::TCP, atoi(port.c_str()));
        this->ss->listen();

        try
        {
            while (true)
            {
                auto socket = this->ss->accept();
                this->pool.add(std::make_unique<Task>(std::move(socket), std::ref(this->manager)));
            }
        }
        catch (ExitException& exit)
        {
            return exit.code();
        }
        catch (Exception& e)
        {
            IO::log("Error encountered", std::cerr);
            IO::log(e.what(), std::cerr);
            return -1;
        }
        return 0;
    }
    Application::Application(int argn, const char** argv)
        : args(argn, argv)
    {
        this->manager.loadPlugins();
    }
}
