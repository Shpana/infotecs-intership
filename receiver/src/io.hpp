#ifndef INFOTECS_IO_HPP
#define INFOTECS_IO_HPP

#include <cstdint>

namespace infotecs {
inline bool IsCorrectData(std::int64_t data) {
  return data >= 100 && (data % 32 == 0);
}
}  // namespace infotecs

#endif  // INFOTECS_IO_HPP
