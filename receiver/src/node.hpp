#ifndef INFOTECS_NODE_HPP
#define INFOTECS_NODE_HPP

#include <cstdint>
#include <string_view>

#include <fmt/core.h>
#include <boost/asio.hpp>

#include "logging.hpp"

namespace asio = boost::asio;
using boost::system::error_code;

namespace infotecs {
namespace details {
const std::size_t kBufferSize = 128;
}

class Node {
 public:
  Node(asio::io_context& context, std::string_view ip_address,
       std::uint16_t port)
      : context_(context),
        endpoint_(asio::ip::address::from_string(ip_address.data()), port) {
  }

  asio::awaitable<std::string> Receive() {
    asio::ip::tcp::socket socket{context_};
    asio::ip::tcp::acceptor acceptor{context_, endpoint_};
    co_await acceptor.async_accept(socket, asio::use_awaitable);

    std::array<char, details::kBufferSize> buffer{};
    co_await socket.async_read_some(asio::buffer(buffer), asio::use_awaitable);

    co_return std::string(buffer.begin(), buffer.end());
  }

 private:
  asio::io_context& context_;
  asio::ip::tcp::endpoint endpoint_;
};
}  // namespace infotecs

#endif  // INFOTECS_NODE_HPP
