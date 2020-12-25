//
// Created by david on 7/16/20.
//

#include <Utils/Foundation/PosixCall.hpp>
#include <constants.hpp>

#include <unistd.h>
#include <sys/wait.h>

namespace greatbridf
{
    int pipe_exec(exec_info* info, byte_array* input_data,
        const ::std::function<void(byte_array*)>& on_stdout,
        const ::std::function<void(byte_array*)>& on_stderr)
    {
        int fd_stdin[2], fd_stdout[2], fd_stderr[2];
        pipe(fd_stdin);
        pipe(fd_stdout);
        pipe(fd_stderr);

        int pid = fork();
        if (pid > 0) // father
        {
            close(fd_stdin[0]);
            close(fd_stdout[1]);
            close(fd_stderr[1]);

            write(fd_stdin[1], input_data->arr, input_data->size);
            close(fd_stdin[1]);

            byte _buf[_GREATBRIDF_BUFFER_SIZE];
            byte_array buf{ _buf, 0 };
            while ((buf.size = read(fd_stdout[0], buf.arr, _GREATBRIDF_BUFFER_SIZE)))
                on_stdout(&buf);
            while ((buf.size = read(fd_stderr[0], buf.arr, _GREATBRIDF_BUFFER_SIZE)))
                on_stderr(&buf);

            int return_status = 0;
            waitpid(pid, &return_status, 0);
            return WEXITSTATUS(return_status);
        }
        // child

        dup2(fd_stdin[0], STDIN_FILENO);
        dup2(fd_stdout[1], STDOUT_FILENO);
        dup2(fd_stderr[1], STDERR_FILENO);

        close(fd_stdin[0]);
        close(fd_stdin[1]);
        close(fd_stdout[0]);
        close(fd_stdout[1]);
        close(fd_stderr[0]);
        close(fd_stderr[1]);

        execve(info->path, info->p_arg, info->p_env);
        // it shouldn't execute to here
        return -1;
    }
}
