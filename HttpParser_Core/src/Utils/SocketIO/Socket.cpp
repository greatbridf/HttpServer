#include <Utils/Foundation/Exceptions/Exception.hpp>
#include <Utils/SocketIO/Socket.hpp>

namespace greatbridf
{

    Socket::Socket(Socket::SocketType type, const char* ip, int port)
    {
        this->socket = ::socket(AF_INET, SOCK_STREAM, int(type));

        if (this->socket < 0)
            throw std::runtime_error("cannot create socket");

        this->ip = ip;
        this->port = port;
        memset(&this->addr, 0, sizeof(sockaddr_in));
        this->addr.sin_family = AF_INET;
        this->addr.sin_addr.s_addr = strcmp(ip, "") == 0 ? INADDR_ANY : inet_addr(ip);
        this->addr.sin_port = htons(port);
    }

    Socket::Socket(int socket, sockaddr_in addr)
    {
        this->socket = socket;
        this->addr = addr;

        this->ip = inet_ntoa(addr.sin_addr);
        this->port = int(ntohs(addr.sin_port));
    }

    Socket::~Socket()
    {
        this->close();
    }

    void Socket::connect()
    {
        auto result = ::connect(this->socket, (sockaddr*)&this->addr, sizeof(this->addr));
        if (result < 0)
        {
            throw Exception("cannot connect to target ip");
        }
    }

    void Socket::close()
    {
        if (this->closed) return;
        this->closed = true;
        ::close(this->socket);
        this->socket = 0;
    }

    const std::string& Socket::getIP() const
    {
        return this->ip;
    }

    int Socket::getPort() const
    {
        return this->port;
    }

    void Socket::setTimeout(int _timeout)
    {
        timeout = _timeout;
        timeval val{ timeout, 0 };
        ::setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, &val, sizeof(val));
        ::setsockopt(socket, SOL_SOCKET, SO_SNDTIMEO, &val, sizeof(val));
    }

    int Socket::getTimeout()
    {
        return timeout;
    }

}