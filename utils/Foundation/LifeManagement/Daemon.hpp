//
// Created by David Mike on 2020/3/2.
//

#ifndef _DAEMON_HPP_
#define _DAEMON_HPP_

#include <utils/Foundation/File.hpp>
#include <utils/Foundation/Exceptions/ExitException.hpp>
#include <zconf.h>
#include <functional>

namespace greatbridf
{
    class Daemon
    {
     public:
        explicit Daemon(std::string _appName);
        Daemon(Daemon& obj) = delete;
        Daemon(const Daemon& obj) = delete;
        pid_t check();

        ExitCode start(const std::function<int()>& func);
        ExitCode stop(pid_t pid);
        static int pError(ExitCode code);
     private:
        std::string appName;
    };
}

#endif //_DAEMON_HPP_
