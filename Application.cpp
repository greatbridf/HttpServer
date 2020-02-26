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

                HTTPRequest request;
                bool keep_alive = false;
                while (stream >> request)
                {
                    HTTPResponse response;
                    if (request.getHeader("Connection") == "keep-alive")
                    {
                        socket->setTimeout(5); // default
                        response.setHeader("Keep-Alive", "timeout=" + std::to_string(socket->getTimeout()));
                        keep_alive = true;
                    }
                    else
                    {
                        response.setHeader("Connection", "close");
                        keep_alive = false;
                    }

                    switch (request.getRequestType())
                    {
                    case HTTPRequestType::GET:
                        Handler::GET(request, stream, response);
                        break;
                    case HTTPRequestType::POST:
                        Handler::POST(request, stream, response);
                        break;
                    default:
                        response.setResponseCode(400);
                        stream << response << std::flush;
                        break;
                    }

                    if (!keep_alive) break;
                }

                stream.setstate(std::ios::eofbit);
            }
            catch (Exception& e)
            {
                IO::log("Error encountered", std::cerr);
                IO::log(e.what(), std::cerr);
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
            IO::log("Error encountered", std::cerr);
            IO::log(e.what(), std::cerr);
            return -1;
        }
        return 0;
    }

}