//
// Created by David Mike on 2020/2/25.
//

#include "SocketBuffer.hpp"

namespace greatbridf
{

    SocketBuffer::SocketBuffer(Socket& socket)
        : socket(socket)
    {
      this->readBuf = new char[BUF_SIZE];
      this->writeBuf = new char[BUF_SIZE];

      setg(this->readBuf, this->readBuf, this->readBuf);
      setp(this->writeBuf, this->writeBuf + BUF_SIZE);
    }

    SocketBuffer::~SocketBuffer()
    {
      delete[] this->readBuf;
      delete[] this->writeBuf;
    }

    int SocketBuffer::underflow()
    {
      size_t n = ::recv(socket.socket, eback(), BUF_SIZE, 0);

      if (n <= 0)
      {
        return EOF;
      }
      else
      {
        setg(eback(), eback(), eback() + n);
      }

      return *eback();
    }

    int SocketBuffer::sync()
    {
      if (socket.closed) return EOF;

      size_t sent = 0;
      size_t total = pptr() - pbase();

      while (sent < total)
      {
        size_t n = ::send(socket.socket, writeBuf, total - sent, 0);

        if (n > 0)
        {
          sent += n;
        }
        else
        {
          return EOF;
        }
      }

      setp(pbase(), pbase() + BUF_SIZE);
      pbump(0);

      return 0;
    }

    int SocketBuffer::overflow(int c)
    {
      if (sync() == EOF)
      {
        return EOF;
      }

      if (c != EOF)
      {
        sputc(c);
      }
      return c;
    }

}
