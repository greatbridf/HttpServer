#include "Application.h"

const static std::string msg = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\nContent-Length: 61\r\n\r\n"
"<!DOCTYPE html><html><body><h1>HelloWorld!</h1></body></html>";

namespace greatbridf {

  Application::~Application() {
    delete this->ss;
  }

  int Application::run() {
    this->ss = new ServerSocket(Socket::SocketType::TCP, 8080);
    this->ss->listen();

    try {
      for (int i = 0; i < 10; ++i) {
        Socket* socket = this->ss->accept();
        std::thread th {
          [](Socket* socket) {
            std::cout << "Thread " << std::this_thread::get_id() << ": launched" << std::endl;
            std::cout << "Thread " << std::this_thread::get_id() << ": connection from " << socket->getIP() << ':' << socket->getPort() << std::endl;
            std::string data;
            *socket >> data;
            *socket << msg;
            delete socket;
            auto re = data.substr(0, data.find("\r\n\r\n"));
            HTTPRequest req(re);
            std::cout << "request body:" << std::endl << data.substr(data.find("\r\n\r\n")+4, data.size()-1) << std::endl;
            std::cout << "Thread " << std::this_thread::get_id() << ": exits" << std::endl;
          }, socket
        };
        th.detach();
      }
    } catch (Exception& e) {
      std::cerr << "Error encountered: " << e.what() << std::endl;
      return -1;
    }
    return 0;
  }

}