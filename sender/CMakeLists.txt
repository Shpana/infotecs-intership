find_package(Boost REQUIRED)
add_executable(sender
    src/main.cpp
    src/logging.hpp
    src/node.hpp
    src/io.hpp
    src/sync/thread_group.hpp
    src/sync/queue.hpp)
target_include_directories(sender
    PRIVATE ${Boost_INCLUDE_DIR})

if (MINGW)
  target_link_libraries(sender
      PRIVATE fmt::fmt ws2_32 wsock32)
elseif ()
  target_link_libraries(sender
      PRIVATE fmt::fmt)
endif ()