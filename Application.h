#ifndef __APPLICATION_HPP_
#define __APPLICATION_HPP_

#include <iostream>
#include <fstream>
#include <memory>

#include <HTTP/HTTPRequest.hpp>
#include <HTTP/HTTPResponse.hpp>
#include <Utils/SocketIO/SocketBuffer.hpp>
#include <Utils/Foundation/BasicIO.hpp>
#include <Utils/Foundation/Plugin/PluginManager.hpp>
#include <Utils/SocketIO/ServerSocket.hpp>
#include <Utils/Thread/Thread.hpp>
#include <Utils/Foundation/LifeManagement/ArgumentParser.hpp>

namespace greatbridf
{
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
}

#endif