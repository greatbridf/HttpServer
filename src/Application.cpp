#include "Application.h"
#include <csignal>

namespace greatbridf
{
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
        this->ss = std::make_unique<ServerSocket>(BasicSocket::Type::TCP, atoi(port.c_str()));
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
        : args(argn, argv)
    {
        if (args.hasOption("--plugins"))
        {
            this->manager.loadPlugins(args.getOption("--plugins"));
        }
        else if (global_configs().has_option("plugin_path"))
        {
            this->manager.loadPlugins(global_configs().global_option("plugin_path"));
        }
        else
        {
            this->manager.loadPlugins(_GREATBRIDF_PLUGIN_DIRECTORY);
        }
    }
}
