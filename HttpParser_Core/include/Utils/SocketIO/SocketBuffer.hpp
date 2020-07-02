//
// Created by David Mike on 2020/2/25.
//

#ifndef HTTPPARSER_SOCKETBUFFER_HPP
#define HTTPPARSER_SOCKETBUFFER_HPP

#include <streambuf>

#include "Socket.hpp"

namespace greatbridf
{

    class SocketBuffer : public std::streambuf
    {
     public:
        const static size_t BUF_SIZE = 16 * 1024;

        explicit SocketBuffer(Socket& socket);
        ~SocketBuffer() override;

     protected:
        // For input (or read)
        int underflow() override;

        // For output (or write)
        int sync() override;
        int overflow(int c) override;

     private:
        Socket& socket;
        char* readBuf = nullptr;
        char* writeBuf = nullptr;

    };

}

#endif //HTTPPARSER_SOCKETBUFFER_HPP
