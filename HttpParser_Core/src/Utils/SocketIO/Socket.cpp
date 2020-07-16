#include <Utils/Foundation/Exceptions/Exception.hpp>
#include <Utils/SocketIO/Socket.hpp>

namespace greatbridf
{
    // BasicSocket
    BasicSocket::BasicSocket(BasicSocket::Type type, const char* ip, unsigned int port)
        : _addr(), _timeout(0), _state(State::Ready)
    {
        this->_socket = ::socket(AF_INET, SOCK_STREAM, int(type));

        if (this->_socket < 0)
            throw Exception("cannot create socket");

        this->_ip = ip;
        this->_port = port;

        memset(&this->_addr, 0, sizeof(sockaddr_in));
        this->_addr.sin_family = AF_INET;
        this->_addr.sin_addr.s_addr = strcmp(ip, "") == 0 ? INADDR_ANY : inet_addr(ip);
        this->_addr.sin_port = htons(port);

        setTimeout(_GREATBRIDF_SOCKET_DEFAULT_TIMEOUT);
    }
    BasicSocket::BasicSocket(int socket, sockaddr_in _addr)
        : _socket(socket), _addr(_addr), _port(ntohs(_addr.sin_port)),
          _ip(inet_ntoa(_addr.sin_addr)), _timeout(0), _state(State::Ready)
    {
        setTimeout(_GREATBRIDF_SOCKET_DEFAULT_TIMEOUT);
    }
    BasicSocket::~BasicSocket()
    {
        this->close();
    }
    unsigned int BasicSocket::port() const
    {
        return _port;
    }
    const std::string& BasicSocket::ip() const
    {
        return _ip;
    }
    int BasicSocket::setTimeout(unsigned int __timeout)
    {
        _timeout = __timeout;
        timeval val{ __timeout, 0 };
        ::setsockopt(_socket, SOL_SOCKET, SO_RCVTIMEO, &val, sizeof(val));
        ::setsockopt(_socket, SOL_SOCKET, SO_SNDTIMEO, &val, sizeof(val));
        return 0;
    }
    unsigned int BasicSocket::timeout() const
    {
        return _timeout;
    }
    void BasicSocket::close()
    {
        if (state() == State::Closed) return;
        if (::close(_socket) == -1)
        {
            throw Exception("cannot close socket");
        }
        _set_state(State::Closed);
    }
    BasicSocket::State BasicSocket::state() const
    {
        return _state;
    }
    void BasicSocket::_set_state(greatbridf::BasicSocket::State state)
    {
        _state = state;
    }

    // Socket
    Socket::Socket(greatbridf::BasicSocket::Type type, const char* ip, unsigned int port)
        : BasicSocket(type, ip, port)
    {
    }
    Socket::Socket(int socket, sockaddr_in addr)
        : BasicSocket(socket, addr)
    {
    }
    void Socket::connect()
    {
        auto result = ::connect(this->_socket, (sockaddr*)&this->_addr, sizeof(this->_addr));
        if (result < 0)
        {
            throw Exception("cannot connect to target ip");
        }
    }
}