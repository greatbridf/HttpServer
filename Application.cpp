#include "Application.h"

const static std::string msg = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\nContent-Length: 61\r\n\r\n"
"<!DOCTYPE html><html><body><h1>HelloWorld!</h1></body></html>";

namespace greatbridf {

  int Application::run() {
    ServerSocket ss = ServerSocket(Socket::SocketType::TCP, 8080);
    ss.listen();

    for (int i = 0; i < 10; ++i) {
      Socket* socket = ss.accept();
      std::thread th {
        [](Socket* socket) {
          std::cout << "Thread " << std::this_thread::get_id() << ": launched" << std::endl;
          std::cout << "Thread " << std::this_thread::get_id() << ": connection from " << socket->getIP() << ':' << socket->getPort() << std::endl;
          std::string data;
          *socket >> data;
          *socket << msg;
          delete socket;
          std::cout << data << std::endl;
          std::cout << "Thread " << std::this_thread::get_id() << ": exits" << std::endl;
        }, socket
      };
      th.detach();
    }

    ss.close();
    return 0;
  }

}