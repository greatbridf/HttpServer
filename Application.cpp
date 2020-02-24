#include "Application.h"

const static std::string msg = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\nConnection: close\r\nContent-Length: 61\r\n\r\n"
"<!DOCTYPE html><html><body><h1>HelloWorld!</h1></body></html>";

namespace greatbridf {

  Application::~Application() {
    delete this->ss;
  }

  class Task : public ITask {
    public:
      Task(Socket* socket): socket(socket) {}
      ~Task() override {
        delete this->socket;
      }

      void run() override {
        try {
          log("Connection from " + socket->getIP() + ':' + std::to_string(socket->getPort()));
          std::string data;
          *socket >> data;
          *socket << msg;

          auto re = data.substr(0, data.find("\r\n\r\n"));
          HTTPRequest req(re);

          log("Request body: ");
          std::cout << data.substr(data.find("\r\n\r\n")+4, data.size()-1) << std::endl;

          log("Exited");

        } catch (Exception& e) {
          log(std::string("Error encountered: ") + e.what(), std::cerr);
        }
      }

      inline void log(std::string msg, std::ostream& stream) {
        stream << "[Thread " << std::this_thread::get_id() << "] " << msg << std::endl;
      }

      inline void log(std::string msg) {
        log(msg, std::cout);
      }

    private:
      Socket* socket = nullptr;
  };

  int Application::run() {
    this->ss = new ServerSocket(Socket::SocketType::TCP, 8080);
    this->ss->listen();

    try {
      for (int i = 0; i < 10; ++i) {
        Socket* socket = this->ss->accept();
        this->pool.add(new Task(socket));
      }
    } catch (Exception& e) {
      std::cerr << "[Main Thread] Error encountered: " << e.what() << std::endl;
      return -1;
    }
    return 0;
  }

}