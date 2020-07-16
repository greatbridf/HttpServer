//
// Created by David Mike on 2020/3/2.
//

#include <csignal>
#include <iostream>
#include <sys/stat.h>
#include <utility>
#include <functional>

#include <Utils/Foundation/LifeManagement/Daemon.hpp>
#include <Utils/Foundation/BasicIO.hpp>
#include <constants.hpp>

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
            std::cerr << _GREATBRIDF_DAEMON_BADARGS << '\n' << std::endl;
            break;
        case AlreadyRunning:
            std::cerr <<_GREATBRIDF_DAEMON_ALREADY_RUNNING << std::endl;
            break;
        case PermissionDenied:
            std::cerr << _GREATBRIDF_DAEMON_PERMISSION_DENIED << std::endl;
            break;
        case NotRunning:
            std::cerr << _GREATBRIDF_DAEMON_NOT_RUNNING << std::endl;
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

        // Set pwd to root ( / )
        chdir("/");

        // Close stdin stdout stderr
        auto null_file = ::fopen("/dev/null", "rw");
        int null_fd = ::fileno(null_file);

        ::dup2(null_fd, STDIN_FILENO);
        ::dup2(null_fd, STDOUT_FILENO);
        ::dup2(null_fd, STDERR_FILENO);
        return static_cast<ExitCode>(func(argn, argv));
    }
}
