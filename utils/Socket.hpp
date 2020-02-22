#include <sys/socket.h>
#include <arpa/inet.h>
#include <memory.h>
#include <netinet/in.h>
#include <unistd.h>

#include <stdexcept>
#include <string>

namespace greatbridf {

  class Socket {
    public:
      enum class SocketType {
        TCP = IPPROTO_TCP,
        UDP = IPPROTO_UDP
      };

      Socket(SocketType type, const char* ip, int port);
      Socket(int socket, sockaddr_in addr);
      ~Socket();

      void send(const char* data, unsigned long long size) const;
      void send(const std::string& data) const;

      const std::string& getIP() const;
      int getPort() const;

      void close();

    protected:
      int socket;

      std::string ip;
      int port;
      sockaddr_in addr;

      bool closed = false;
  };

}