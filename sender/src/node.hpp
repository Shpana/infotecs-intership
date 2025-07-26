#ifndef INFOTECS_NODE_HPP
#define INFOTECS_NODE_HPP

#include <boost/asio.hpp>
#include <fmt/core.h>

#include "logging.hpp"

namespace asio = boost::asio;
using boost::system::error_code;

namespace infotecs {
class Node {
 public:
  Node(asio::io_context& context, std::string_view ip_address,
       std::uint16_t port)
      : context_(context),
        endpoint_(asio::ip::address::from_string(ip_address.data()), port) {
  }

  asio::awaitable<void> Send(std::int64_t message) {
    asio::ip::tcp::socket socket{context_};
    try {
      co_await socket.async_connect(endpoint_, asio::use_awaitable);
    } catch (boost::system::system_error& exc) {
      LOG_ERROR() << fmt::format("Connection to receiver failed via: {}\n",
                                 exc.what());
      co_return;
    }
    std::array<std::int64_t, 1> buffer = {message};
    co_await socket.async_write_some(asio::buffer(buffer), asio::use_awaitable);
  }

 private:
  asio::io_context& context_;
  asio::ip::tcp::endpoint endpoint_;
};
}  // namespace infotecs

#endif  // INFOTECS_NODE_HPP
