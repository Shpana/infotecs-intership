find_package(Boost REQUIRED)
add_executable(receiver
    src/main.cpp
    src/logging.hpp
    src/node.hpp
    src/io.hpp)
target_include_directories(receiver
    PRIVATE ${Boost_INCLUDE_DIR})

if (MINGW)
  target_link_libraries(receiver
      PRIVATE fmt::fmt ws2_32 wsock32)
elseif ()
  target_link_libraries(receiver
      PRIVATE fmt::fmt)
endif ()