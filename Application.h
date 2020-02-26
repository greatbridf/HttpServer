#include <iostream>
#include <fstream>

#include "utils/ServerSocket.hpp"
#include "HTTP/HTTPRequest.hpp"
#include "utils/multi-threading/Thread.hpp"

namespace greatbridf
{
    class Application
    {
     public:
        int run();
        ~Application();

     private:
        ServerSocket* ss = nullptr;
        ThreadPool pool;
    };
}