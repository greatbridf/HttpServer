#ifndef __APPLICATION_HPP_
#define __APPLICATION_HPP_

#include <iostream>
#include <fstream>
#include <memory>
#include <regex>

#include <HttpParser_Core.hpp>
#include <marco_definitions.hpp>
#include <Configurations.hpp>

namespace greatbridf
{
    // Global configuration
    const Configurations& global_configs();

    class Application
    {
     public:
        explicit Application(int argn, const char** argv);
        int run();

     private:
        std::unique_ptr<ServerSocket> ss;
        ThreadPool pool;
        PluginManager manager{};
        ArgumentParser args;
    };

    class RequestHandler : public virtual ITask
    {
     private:
        std::unique_ptr<Socket> socket;
        PluginManager& manager;

     public:
        RequestHandler(std::unique_ptr<Socket> _socket, PluginManager& _manager);
        void run() override;
    };
}

#endif