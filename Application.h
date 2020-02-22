#include <iostream>
#include <thread>

#include "utils/ServerSocket.hpp"
#include "HTTP/HTTPRequest.hpp"

namespace greatbridf {
  class Application {
    public:
      int run();
      ~Application();
    private:
      ServerSocket* ss = nullptr;
  };
}