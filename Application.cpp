#include "Application.h"
#include <signal.h>

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
                while (stream >> request)
                {
                    HTTPResponse response;
                    if (request.getHeader("Connection") == "keep-alive")
                    {
                        socket->setTimeout(5); // default
                        response.setHeader("Keep-Alive", "timeout=" + std::to_string(socket->getTimeout()));
                        keep_alive = true;
                    }
                    else
                    {
                        response.setHeader("Connection", "close");
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
        this->ss = std::make_unique<ServerSocket>(Socket::SocketType::TCP, 8080);
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
    Application::Application()
    {
        this->manager.loadPlugins();
    }
}
