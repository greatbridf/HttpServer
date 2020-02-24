#include "ServerSocket.hpp"

namespace greatbridf {

  ServerSocket::ServerSocket(Socket::SocketType type, int port) : Socket(type, "127.0.0.1", port) {

    int code = bind(this->socket, (sockaddr*)&this->addr, sizeof(sockaddr));
    if (code < 0)
      throw std::runtime_error("unable to bind port");
  }

  ServerSocket::~ServerSocket() = default;

  void ServerSocket::listen() {
    int code = ::listen(this->socket, queueLength);
    if (code < 0)
      throw std::runtime_error("unable to listen");
  }

  Socket* ServerSocket::accept() {
    sockaddr_in addr{};
    int len = sizeof(sockaddr_in);

    int socket = ::accept(this->socket, (sockaddr*)&addr, (socklen_t*)&len);
    if (socket < 0)
      throw std::runtime_error("cannot accept connection");
    
    return new Socket(socket, addr);
  }

}