cmake_minimum_required(VERSION 3.0.2)
project(tcp_sample)

## Compile as C++11
add_compile_options(-std=c++11)

include_directories(
    include
)

find_package(Threads REQUIRED)

add_executable(server.out src/server.cpp src/chat_server.cpp)
add_executable(client.out src/client.cpp)

target_link_libraries(server.out Threads::Threads)