//
// Created by David Mike on 2020/2/26.
//

#ifndef _BASICIO_HPP_
#define _BASICIO_HPP_

#include <iostream>
#include <thread>

namespace greatbridf
{
    namespace IO
    {
        template<typename T>
        void log(T msg, std::ostream& os = std::cout)
        {
            os << "[Thread " << std::this_thread::get_id() << "] " << msg << std::endl;
        }
    }
}

#endif //_BASICIO_HPP_
