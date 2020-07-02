#ifndef __SERVERSOCKET_HPP_
#define __SERVERSOCKET_HPP_

#include "Socket.hpp"
#include <cerrno>
#include <memory>

#include <Utils/Foundation/Exceptions/ExitException.hpp>

namespace greatbridf
{

    class ServerSocket : public Socket
    {
     public:
        ServerSocket(Socket::SocketType type, int port);
        ServerSocket(ServerSocket& ss) = delete;
        ServerSocket(const ServerSocket& ss) = delete;
        ~ServerSocket();

        void listen();
        std::unique_ptr<Socket> accept();

        const static unsigned int queueLength = 5;
    };

}

#endif