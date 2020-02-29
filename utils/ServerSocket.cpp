#include <Application.h>
#include <cerrno>
#include "ServerSocket.hpp"

namespace greatbridf
{

    ServerSocket::ServerSocket(Socket::SocketType type, int port)
        : Socket(type, "", port)
    {

        const static int opt = 1;
        ::setsockopt(this->socket, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));

        int code = bind(this->socket, (sockaddr*)&this->addr, sizeof(sockaddr));
        if (code < 0)
            throw std::runtime_error("unable to bind port");
    }

    ServerSocket::~ServerSocket() = default;

    void ServerSocket::listen()
    {
        int code = ::listen(this->socket, queueLength);
        if (code < 0)
            throw std::runtime_error("unable to listen");
    }

    std::unique_ptr<Socket> ServerSocket::accept()
    {
        sockaddr_in addr{};
        int len = sizeof(sockaddr_in);

        int socket = ::accept(this->socket, (sockaddr*)&addr, (socklen_t*)&len);
        if (socket < 0)
        {
            if (errno == 9)
            {
                throw Application::ExitApplication();
            }
            else
            {
                throw std::runtime_error("cannot accept connection");
            }
        }

        return std::make_unique<Socket>(socket, addr);
    }

}