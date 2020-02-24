#include "Application.h"

namespace greatbridf {

  const static std::string getRet = "HTTP/1.1 200 OK\r\n"
                                    "Content-Type: text/html\r\n"
                                    "Connection: close\r\n"
                                    "Content-Length: ";

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

          HTTPRequest req(data);

          log("Request body: ");
          std::cout << req.getRequestBody() << std::endl;

          switch (req.getRequestType()) {
            default:
              log("Unsupported request type");
              break;

            case HTTPRequest::RequestType::GET:
              auto path = req.getQueryPath();
              if (path == "/") {
                path = "/index.html";
              }

              std::fstream fs("." + path);
              if (!fs.good()) {
                throw Exception("Not found");
              }

              fs.seekg(0, std::ios::end);
              *socket << getRet << std::to_string(fs.tellg()) << "\r\n\r\n";
              fs.seekg(0, std::ios::beg);

              std::string tmp;
              while (!fs.eof()) {
                std::getline(fs, tmp, '\n');
                *socket << tmp << "\n";
              }
              *socket << "\r\n";

              break;
          }

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
      for (int i = 0; i < 3; ++i) {
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