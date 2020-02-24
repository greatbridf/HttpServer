#include "Thread.hpp"

namespace greatbridf {
  ThreadPool::ThreadPool() = default;

  ThreadPool::~ThreadPool() {
    this->recycle();

    for (auto& item : workers) {
      if (item.second.joinable()) {
        item.second.join();
      }
    }

    for (auto& item : tasks) {
      delete item.second;
    }
  }

  void ThreadPool::add(ITask* task) {
    this->recycle();

    std::thread th{
      [](ITask* task, std::queue<std::thread::id>* queue, std::mutex* mtx) {
        task->run();

        std::lock_guard<std::mutex> lck(*mtx);
        queue->push(std::this_thread::get_id());
      }, task, &this->finQueue, &this->mtx
    };
    auto id = th.get_id();
    this->tasks.insert(std::make_pair(id, task));
    this->workers.insert(std::make_pair(id, std::move(th)));
  }

  void ThreadPool::recycle() {

    while (!this->finQueue.empty()) {

      auto id = this->finQueue.front();
      if (this->workers.at(id).joinable()) this->workers.at(id).join();

      this->workers.erase(id);

      delete this->tasks.at(id);
      this->tasks.erase(id);

      this->finQueue.pop();
    }
  }

}