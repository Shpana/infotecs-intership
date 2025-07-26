#ifndef INFOTECS_THREAD_GROUP_HPP
#define INFOTECS_THREAD_GROUP_HPP

#include <functional>
#include <thread>
#include <vector>

namespace infotecs::sync {
class ThreadGroup {
  using Task = std::function<void()>;

 public:
  void Submit(Task task) {
    workers_.emplace_back(std::move(task));
  }

  void WaitAll() {
    for (auto&& worker : workers_) {
      if (worker.joinable()) {
        worker.join();
      }
    }
  }

 private:
  std::vector<std::thread> workers_{};
};
}  // namespace infotecs::sync

#endif  // INFOTECS_THREAD_GROUP_HPP
