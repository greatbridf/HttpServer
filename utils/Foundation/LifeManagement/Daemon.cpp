//
// Created by David Mike on 2020/3/2.
//

#include <csignal>
#include <iostream>
#include <sys/stat.h>
#include <utility>
#include <functional>

#include "Daemon.hpp"
#include <Static/CommandLineOutput.hpp>
#include <utils/Foundation/BasicIO.hpp>

namespace greatbridf
{
    inline std::string pidFileName(const std::string& appName)
    {
        return "/var/run/" + appName + ".pid";
    }
    Daemon::Daemon(std::string _appName)
        : appName(std::move(_appName))
    {
    }
    pid_t Daemon::check()
    {
        pid_t pid = 0;
        InputFile file(pidFileName(this->appName));
        if (!file.exist())
        {
            return 0;
        }
        file >> pid;
        return pid;
    }
    ExitCode Daemon::stop(pid_t pid)
    {
        if (pid == 0)
        {
            return ExitCode::NotRunning;
        }
        auto file = File(pidFileName(this->appName));
        if (!file.writable() || kill(pid, SIGINT) != 0)
        {
            return ExitCode::PermissionDenied;
        }
        file.remove();
        return ExitCode::Normal;
    }
    int Daemon::pError(ExitCode code)
    {
        switch (code)
        {
        case BadArgs:
            std::cerr << Static::CommandLineOutput::badArgs << '\n'
                      << Static::CommandLineOutput::help << std::endl;
            break;
        case AlreadyRunning:
            std::cerr << Static::CommandLineOutput::alreadyRunning << std::endl;
            break;
        case PermissionDenied:
            std::cerr << Static::CommandLineOutput::permissionDenied << std::endl;
            break;
        case NotRunning:
            std::cerr << Static::CommandLineOutput::notRunning << std::endl;
            break;
        case Normal:
        default:
            break;
        }
        return code;
    }
    ExitCode Daemon::start(const std::function<int(int, const char**)>& func, int argn, const char** argv)
    {
        if (this->check())
        {
            return ExitCode::AlreadyRunning;
        }
        auto file = OutputFile(pidFileName(this->appName));
        if (!file.writable())
        {
            return ExitCode::PermissionDenied;
        }
        auto pid = fork();
        if (pid != 0)
        {
            IO::log("Running (PID" + std::to_string(pid) + ')');
            file << pid << std::flush;
            return ExitCode::Normal;
        }

        // Child process
        signal(SIGHUP, SIG_IGN);
        signal(SIGPIPE, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
        signal(SIGTERM, SIG_IGN);

        // Create session
        setsid();
        // Set UMask
        umask(0);
        // TODO: close stdio
        return static_cast<ExitCode>(func(argn, argv));
    }
}
