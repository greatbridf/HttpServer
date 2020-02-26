#include <HTTP/HTTPResponse.hpp>
#include <utils/SocketIO/SocketBuffer.hpp>
#include <utils/Foundation/File.hpp>
#include <utils/Foundation/StreamIOHelper.hpp>
#include <utils/Foundation/BasicIO.hpp>
#include "Application.h"

namespace greatbridf
{

    Application::~Application()
    {
      delete this->ss;
    }

    class Task : public ITask
    {
     public:
        explicit Task(Socket* socket)
            : socket(socket)
        {
        };
        ~Task() override
        {
          delete this->socket;
        }

        void run() override
        {
          try
          {
            IO::log("Connection from " + socket->getIP() + ':' + std::to_string(socket->getPort()));
            SocketBuffer buffer(*socket);
            std::iostream stream(&buffer);

            HTTPRequest req;
            stream >> req;

            switch (req.getRequestType())
            {

            case HTTPRequestType::GET:
            {
              auto path = req.getQueryPath();
              if (path == "/")
              {
                path = "/index.html";
              }

              File file("." + path);
              if (!file.good())
              {
                stream << HTTPResponse(404) << std::flush;
                break;
              }

              HTTPResponse response(200, HTTPVersion::ONE);
              response.setHeader("Content-Length", file.fileSize());
              stream << response;
              redirectStream(stream, file, file.fileSize());

              break;
            }

            case HTTPRequestType::POST:
            {

              HTTPResponse response(200);

              auto length = req.bodySize();
              if (length > 0)
              {
                response.setHeader("Content-Length", length);
                stream << response;
                redirectStream(stream, stream, length);
              }
              else
              {
                stream << response << std::flush;
                IO::log("Request body empty");
              }

              break;
            }

            default:
            {
              stream << HTTPResponse(400) << std::flush;
              break;
            }
            }

            IO::log("Exited");

          }
          catch (Exception& e)
          {
            IO::log(std::string("Error encountered: ") + e.what(), std::cerr);
          }
        }

     private:
        Socket* socket = nullptr;
    };

    int Application::run()
    {
      this->ss = new ServerSocket(Socket::SocketType::TCP, 8080);
      this->ss->listen();

      try
      {
        while (true)
        {
          Socket* socket = this->ss->accept();
          this->pool.add(new Task(socket));
        }
      }
      catch (Exception& e)
      {
        std::cerr << "[Main Thread] Error encountered: " << e.what() << std::endl;
        return -1;
      }
      return 0;
    }

}