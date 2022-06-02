project(client)

add_executable(client
    ../common/src/PlayerState.cpp
    src/main.cpp
)

find_package(SDL2 REQUIRED)

target_include_directories(client PRIVATE
    ../common/include
    ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(client
    ${SDL2_LIBRARIES}
    ${Boost_LIBRARIES}
    Threads::Threads
)