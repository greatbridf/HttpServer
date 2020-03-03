#ifndef __APPLICATION_HPP_
#define __APPLICATION_HPP_

#include <iostream>
#include <fstream>
#include <memory>

#include <Handler/GETHandler.hpp>
#include <Handler/POSTHandler.hpp>
#include <HTTP/HTTPRequest.hpp>
#include <HTTP/HTTPResponse.hpp>
#include <utils/SocketIO/SocketBuffer.hpp>
#include <utils/Foundation/BasicIO.hpp>
#include <utils/ServerSocket.hpp>
#include <utils/multi-threading/Thread.hpp>

namespace greatbridf
{
    class Application
    {
     public:
        int run();

     private:
        std::unique_ptr<ServerSocket> ss;
        ThreadPool pool;
    };
}

#endif