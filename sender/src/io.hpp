#ifndef INFOTECS_IO_HPP
#define INFOTECS_IO_HPP

#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>

namespace infotecs {
inline bool IsCorrectInput(const std::string& input) {
  return input.size() <= 64 &&
         std::all_of(input.begin(), input.end(), [](char c) {
           return '0' <= c && c <= '9';
         });
}

inline std::string TransformInput(std::string input) {
  std::sort(input.begin(), input.end());

  std::stringstream ss{};
  std::transform(input.begin(), input.end(),
                 std::ostream_iterator<std::string>(ss),
                 [](char c) -> std::string {
                   return ((c - '0') % 2 == 0) ? "KB" : std::string{c};
                 });
  return ss.str();
}
}  // namespace infotecs

#endif  // INFOTECS_IO_HPP
