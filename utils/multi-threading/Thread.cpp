#include "Thread.hpp"
#include <mutex>

namespace greatbridf
{
    ThreadPool::~ThreadPool()
    {
        this->recycle();

        for (auto& item : workers)
        {
            if (item.second.joinable())
            {
                item.second.join();
            }
        }
    }

    void ThreadPool::add(std::unique_ptr<ITask> task)
    {
        this->recycle();

        std::thread th{
            [](std::unique_ptr<ITask> task, std::queue<std::thread::id>& queue, std::mutex& _mtx)
            {
                task->run();

                std::lock_guard<std::mutex> lck(_mtx);
                queue.push(std::this_thread::get_id());
            }, std::move(task), std::ref(this->finQueue), std::ref(this->mtx)
        };
        auto id = th.get_id();
        this->workers.insert(std::make_pair(id, std::move(th)));
    }

    void ThreadPool::recycle()
    {
        while (!this->finQueue.empty())
        {
            auto id = this->finQueue.front();
            if (this->workers.at(id).joinable())
            {
                this->workers.at(id).join();
            }
            this->workers.erase(id);
            this->finQueue.pop();
        }
    }

}
