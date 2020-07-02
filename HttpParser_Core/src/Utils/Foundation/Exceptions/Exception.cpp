#include <Utils/Foundation/Exceptions/Exception.hpp>

namespace greatbridf
{

    Exception::Exception(const char* msg)
    {
        this->msg = msg;
    }

    const char* Exception::what() const noexcept
    {
        return this->msg.c_str();
    }

}