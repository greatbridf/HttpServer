#include "Socket.hpp"
#include <memory>

namespace greatbridf
{

    class ServerSocket : public Socket
    {
     public:
        ServerSocket(Socket::SocketType type, int port);
        ~ServerSocket();

        void listen();
        std::unique_ptr<Socket> accept();

        const static unsigned int queueLength = 5;
    };

}