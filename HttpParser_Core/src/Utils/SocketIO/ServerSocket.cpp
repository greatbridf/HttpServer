#include <Utils/SocketIO/ServerSocket.hpp>

namespace greatbridf
{

    ServerSocket::ServerSocket(BasicSocket::Type type, unsigned int port)
        : BasicSocket(type, "", port)
    {
        const static int opt = 1;
        ::setsockopt(this->_socket, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));

        int code = bind(this->_socket, (sockaddr*)&this->_addr, sizeof(sockaddr));
        if (code < 0)
            throw Exception("unable to bind port");
    }

    void ServerSocket::listen()
    {
        int code = ::listen(this->_socket, queueLength);
        if (code < 0)
            throw Exception("unable to listen");
    }

    std::unique_ptr<Socket> ServerSocket::accept()
    {
        sockaddr_in addr{};
        int len = sizeof(sockaddr_in);

        int socket = ::accept(this->_socket, (sockaddr*)&addr, (socklen_t*)&len);
        if (socket < 0)
        {
            if (errno == 9)
            {
                throw ExitException(ExitCode::Normal);
            }
            else
            {
                throw Exception("cannot accept connection");
            }
        }

        return std::make_unique<Socket>(socket, addr);
    }

}