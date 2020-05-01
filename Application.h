#ifndef __APPLICATION_HPP_
#define __APPLICATION_HPP_

#include <iostream>
#include <fstream>
#include <memory>

#include <HTTP/HTTPRequest.hpp>
#include <HTTP/HTTPResponse.hpp>
#include <utils/SocketIO/SocketBuffer.hpp>
#include <utils/Foundation/BasicIO.hpp>
#include <utils/Foundation/Plugin/PluginManager.hpp>
#include <utils/SocketIO/ServerSocket.hpp>
#include <utils/multi-threading/Thread.hpp>

namespace greatbridf
{
    class Application
    {
     public:
        explicit Application();
        int run();

     private:
        std::unique_ptr<ServerSocket> ss;
        ThreadPool pool;
        PluginManager manager{};
    };
}

#endif