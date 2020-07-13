#include "Application.h"
#include <csignal>

namespace greatbridf
{
    // TODO: a better way instead of global objects
    extern "C" Application* app = nullptr;

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
                this->pool.add(std::make_unique<RequestHandler>(std::move(socket), std::ref(this->manager)));
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
        : args(argn, argv), _configs((const std::string&)_GREATBRIDF_CONFIG_PATH)
    {
        if (args.hasOption("--plugins"))
        {
            this->manager.loadPlugins(args.getOption("--plugins"));
        }
        else if (_configs.has_option("plugin_path"))
        {
            this->manager.loadPlugins(_configs.global_option("plugin_path"));
        }
        else
        {
            this->manager.loadPlugins(_GREATBRIDF_PLUGIN_DIRECTORY);
        }
    }
    const Configurations& Application::configs() const
    {
        return _configs;
    }
}
