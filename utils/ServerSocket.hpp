#include "Socket.hpp"

namespace greatbridf
{

    class ServerSocket : public Socket
    {
     public:
        ServerSocket(Socket::SocketType type, int port);
        ~ServerSocket();

        void listen();
        Socket* accept();

        const static unsigned int queueLength = 5;
    };

}