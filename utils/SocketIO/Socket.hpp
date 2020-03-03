#ifndef HTTPPARSER_SOCKET_HTTP
#define HTTPPARSER_SOCKET_HTTP

#include <sys/socket.h>
#include <arpa/inet.h>
#include <memory.h>
#include <netinet/in.h>
#include <unistd.h>

#include <stdexcept>
#include <string>

namespace greatbridf
{

    class Socket
    {
        friend class SocketBuffer;

     public:
        const static unsigned long BUFSIZE = 1024;

        enum class SocketType
        {
            TCP = IPPROTO_TCP,
            UDP = IPPROTO_UDP
        };

        Socket(SocketType type, const char* ip, int port);
        Socket(int socket, sockaddr_in addr);
        Socket(Socket& obj) = delete;
        Socket(const Socket& obj) = delete;
        ~Socket();

        const std::string& getIP() const;
        int getPort() const;

        void setTimeout(int _timeout);
        int getTimeout();

        void close();

     protected:
        int socket;

        std::string ip;
        int port;
        sockaddr_in addr{};

        int timeout;
        bool closed = false;
    };

}

#endif