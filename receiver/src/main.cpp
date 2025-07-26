#include "node.hpp"

using namespace infotecs;

namespace {
const std::string kIpAddress = "127.0.0.1";
const std::uint16_t kPort = 5000;
}  // namespace

int main() {
  asio::io_context context{};
  asio::co_spawn(
      context.get_executor(),
      [&context]() {
        return [](asio::io_context& context) -> asio::awaitable<void> {
          Node node{context, kIpAddress, kPort};

          while (!context.stopped()) {
            auto result = co_await node.Receive();
            std::cout << result << '\n';
          }
        }(context);
      },
      asio::detached);
  context.run();
}