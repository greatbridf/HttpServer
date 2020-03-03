#ifndef __THREAD_HPP_
#define __THREAD_HPP_

#include <map>
#include <queue>
#include <thread>
#include <vector>
#include <memory>

#include "ITask.hpp"

namespace greatbridf
{
    class ThreadPool
    {
     public:
        ThreadPool() = default;
        ThreadPool(ThreadPool& tp) = delete;
        ThreadPool(const ThreadPool& tp) = delete;
        ~ThreadPool();

        void add(std::unique_ptr<ITask> task);
        void recycle();

     private:
        std::map<std::thread::id, std::thread> workers;
        std::queue<std::thread::id> finQueue;

        std::mutex mtx;
    };

}

#endif