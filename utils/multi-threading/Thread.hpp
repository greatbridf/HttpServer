#pragma once

#include <map>
#include <queue>
#include <thread>
#include <vector>

#include "ITask.hpp"

namespace greatbridf
{

    class ThreadPool
    {
     public:
        ThreadPool();
        ~ThreadPool();

        void add(ITask* task);
        void recycle();

     private:
        std::map<std::thread::id, ITask*> tasks;
        std::map<std::thread::id, std::thread> workers;
        std::queue<std::thread::id> finQueue;

        std::mutex mtx;
    };

}