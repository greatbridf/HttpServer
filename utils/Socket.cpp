#include "Socket.hpp"

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
      this->addr.sin_addr.s_addr = inet_addr(ip);
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

    void Socket::close()
    {
      if (this->closed) return;
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

}