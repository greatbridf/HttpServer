#include "Socket.hpp"

namespace greatbridf {

  Socket::Socket(Socket::SocketType type, const char* ip, int port) {
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

  Socket::Socket(int socket, sockaddr_in addr) {
    this->socket = socket;
    this->addr = addr;

    this->ip = inet_ntoa(addr.sin_addr);
    this->port = int(ntohs(addr.sin_port));
  }

  Socket::~Socket() {
    this->close();
  }

  void Socket::close() {
    if (this->closed) return;
    ::close(this->socket);
    this->socket = 0;
  }

  void Socket::send(const char* data, unsigned long long size) const {
    unsigned long long s = ::send(this->socket, data, size, 0);
    if (s != size) {
      std::string msg = "unable to send (";
      msg += s;
      msg += " byte(s) sent)";
      throw std::runtime_error(msg);
    }
  }

  void Socket::send(const std::string& data) const {
    this->send(data.c_str(), data.size());
  }

  const std::string& Socket::getIP() const {
    return this->ip;
  }

  int Socket::getPort() const {
    return this->port;
  }

  Socket& Socket::operator<<(const std::string& data) {
    this->send(data);
    return *this;
  }

  Socket& Socket::operator>>(std::string& target) {
    char* buf = new char[this->BUFSIZE];
    int nRecv = 0;
    while ((nRecv = ::recv(this->socket, buf, this->BUFSIZE-1, 0)) > 0) {
      buf[nRecv] = 0x00;
      target.append(buf);
      if (target.find("\r\n\r\n") != std::string::npos) break;
    }
    return *this;
  }

}