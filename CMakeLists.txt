cmake_minimum_required(VERSION 3.0.0)
project(online-game)

find_package(Boost REQUIRED)

add_subdirectory(server)
add_subdirectory(client)