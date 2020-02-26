#include <HTTP/HTTPResponse.hpp>
#include <utils/SocketIO/SocketBuffer.hpp>
#include "Application.h"

namespace greatbridf {

  Application::~Application() {
    delete this->ss;
  }

  class Task : public ITask {
    public:
      explicit Task(Socket* socket): socket(socket) {};
      ~Task() override {
        delete this->socket;
      }

      void run() override {
        try {
          log("Connection from " + socket->getIP() + ':' + std::to_string(socket->getPort()));
          SocketBuffer buffer(*socket);
          std::iostream stream(&buffer);

          HTTPRequest req;
          stream >> req;

          log("Request body: ");
          log(stream.eof() ? "EOF" : "NOT_EOF");

          switch (req.getRequestType()) {

            // TODO New File class
            case HTTPRequestType::GET: {
              auto path = req.getQueryPath();
              if (path == "/") {
                path = "/index.html";
              }

              std::fstream fs("." + path);
              if (!fs.good()) {
                stream << HTTPResponse(404);
                break;
              }

              fs.seekg(0, std::ios::end);
              size_t fileSize = fs.tellg();
              fs.seekg(0, std::ios::beg);

              char* content = new char[fileSize];
              fs.read(content, fileSize);
              HTTPResponse response(200, HTTPVersion::ONE);
              response.setHeader("Content-Length", std::to_string(fileSize).c_str());
              stream << response;
              stream.write(content, fileSize);
              stream.flush();
              delete [] content;

              break;
            }

            default: {
              stream << HTTPResponse(400);
              break;
            }
          }

          log("Exited");

        } catch (Exception& e) {
          log(std::string("Error encountered: ") + e.what(), std::cerr);
        }
      }

      inline static void log(const std::string& msg, std::ostream& stream) {
        stream << "[Thread " << std::this_thread::get_id() << "] " << msg << std::endl;
      }

      inline static void log(const std::string& msg) {
        log(msg, std::cout);
      }

    private:
      Socket* socket = nullptr;
  };

  int Application::run() {
    this->ss = new ServerSocket(Socket::SocketType::TCP, 8080);
    this->ss->listen();

    try {
      while (true) {
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