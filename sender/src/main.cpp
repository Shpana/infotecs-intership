#include <iostream>

#include "io.hpp"
#include "node.hpp"
#include "sync/queue.hpp"
#include "sync/thread_group.hpp"

using namespace infotecs;

namespace {
const std::string kIpAddress = "127.0.0.1";
const std::uint16_t kPort = 5000;
}  // namespace

int main() {
  sync::ThreadGroup group{};

  std::atomic<bool> is_running{true};
  sync::BlockingQueue<std::string> queue{};

  // Wait and process user input
  group.Submit([&is_running, &queue]() {
    std::string input;
    while (is_running.load()) {
      std::cin >> input;
      if (!IsCorrectInput(input)) {
        continue;
      }
      queue.Push(SortAndReplace(std::move(input)));
    }
  });

  // Send processed user input to receiver
  group.Submit([&queue]() {
    asio::io_context context{};
    asio::co_spawn(
        context.get_executor(),
        [&context, &queue]() {
          return [](asio::io_context& context,
                    sync::BlockingQueue<std::string>& queue)
                     -> asio::awaitable<void> {
            Node node{context, kIpAddress, kPort};

            while (!context.stopped()) {
              auto result = queue.Pop();
              std::cout << result << '\n';
              co_await node.Send(SumDigits(result));
            }
          }(context, queue);
        },
        asio::detached);
    context.run();
  });

  group.WaitAll();
}