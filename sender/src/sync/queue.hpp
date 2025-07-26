#ifndef INFOTECS_QUEUE_HPP
#define INFOTECS_QUEUE_HPP

#include <condition_variable>
#include <mutex>
#include <queue>

namespace infotecs::sync {
template <typename T>
class BlockingQueue {
 public:
  void Push(T value) {
    std::lock_guard guard{mutex_};
    queue_.push(std::move(value));
    not_empty_.notify_one();
  }

  T Pop() {
    std::unique_lock lock{mutex_};
    while (queue_.empty()) {
      not_empty_.wait(lock);
    }
    auto result = std::move(queue_.front());
    queue_.pop();
    return result;
  }

 private:
  std::queue<T> queue_{};  // Guarded by mutex_
  std::mutex mutex_{};
  std::condition_variable not_empty_{};
};
}  // namespace infotecs::sync

#endif  // INFOTECS_QUEUE_HPP
