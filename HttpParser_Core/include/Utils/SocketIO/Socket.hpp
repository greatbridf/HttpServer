#ifndef HTTPPARSER_SOCKET_HTTP
#define HTTPPARSER_SOCKET_HTTP

#include <sys/socket.h>
#include <arpa/inet.h>
#include <memory.h>
#include <netinet/in.h>
#include <unistd.h>

#include <stdexcept>
#include <string>

#include "../Foundation.hpp"
#include "../../constants.hpp"

namespace greatbridf
{
    class BasicSocket : public NonCopyable
    {
     public:
        const static size_t _buf_size = _GREATBRIDF_BUFFER_SIZE;
        enum class Type
        {
            TCP = IPPROTO_TCP,
            UDP = IPPROTO_UDP
        };

        enum class State
        {
            Ready,
            Listening,
            Connected,
            Closed
        };

        BasicSocket(Type type, const char* ip, unsigned int port);
        BasicSocket(int socket, sockaddr_in addr);
        ~BasicSocket();

        const std::string& ip() const;
        unsigned int port() const;

        int setTimeout(unsigned int _timeout);
        unsigned int timeout() const;

        State state() const;

        void close();

     protected:
        int _socket;

        std::string _ip;

        unsigned int _port;

        sockaddr_in _addr;

        unsigned int _timeout;

        State _state;

        void _set_state(State state);
    };

    class Socket : public BasicSocket
    {
        friend class SocketBuffer;

     public:
        Socket(Type type, const char* ip, unsigned int port);
        Socket(int socket, sockaddr_in addr);

        void connect();
    };

}

#endif