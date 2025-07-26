#ifndef INFOTECS_IO_HPP
#define INFOTECS_IO_HPP

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <numeric>
#include <sstream>
#include <string>

namespace infotecs {
namespace details {
inline bool IsDigit(char c) {
  return '0' <= c && c <= '9';
}
}  // namespace details

inline bool IsCorrectInput(const std::string& input) {
  return input.size() <= 64 &&
         std::all_of(input.begin(), input.end(), [](char c) {
           return details::IsDigit(c);
         });
}

inline std::string SortAndReplace(std::string input) {
  std::sort(input.begin(), input.end());

  std::stringstream ss{};
  std::transform(input.begin(), input.end(),
                 std::ostream_iterator<std::string>(ss),
                 [](char c) -> std::string {
                   return ((c - '0') % 2 == 0) ? "KB" : std::string{c};
                 });
  return ss.str();
}

inline std::int64_t SumDigits(const std::string& message) {
  std::int64_t result{0};
  for (auto c : message) {
    if (details::IsDigit(c)) {
      result += c - '0';
    }
  }
  return result;
}
}  // namespace infotecs

#endif  // INFOTECS_IO_HPP
