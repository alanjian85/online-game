cmake_minimum_required(VERSION 3.0.0)
project(online-game)

find_package(Boost REQUIRED COMPONENTS system)
find_package(Threads REQUIRED)

add_subdirectory(server)
add_subdirectory(client)