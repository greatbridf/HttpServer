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
        class ExitApplication : public Exception
        {
         public:
            explicit ExitApplication(int _code = 0);
            int code() const;
         private:
            int __code = -1;
        };
        int run();

     private:
        std::unique_ptr<ServerSocket> ss;
        ThreadPool pool;
    };
}

#endif