#pragma once

#include <exception>
#include <string>

namespace greatbridf
{

    class Exception : public std::exception
    {
     public:
        explicit Exception(const char* msg);
        explicit Exception(std::string msg);

        const char* what() const noexcept override;

     private:
        std::string msg;
    };

}
