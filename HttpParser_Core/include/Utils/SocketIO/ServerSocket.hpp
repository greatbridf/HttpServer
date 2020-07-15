#ifndef __SERVERSOCKET_HPP_
#define __SERVERSOCKET_HPP_

#include "Socket.hpp"
#include <cerrno>
#include <memory>

#include "../Foundation/Exceptions/ExitException.hpp"

namespace greatbridf
{

    class ServerSocket : public BasicSocket
    {
     public:
        ServerSocket(BasicSocket::Type type, unsigned int port);

        void listen();
        std::unique_ptr<Socket> accept();

        const static unsigned int queueLength = _GREATBRIDF_SOCKET_QUEUE_MAX_LENGTH;
    };

}

#endif