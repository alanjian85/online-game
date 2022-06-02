project(client)

add_executable(client
    src/main.cpp
)

find_package(SDL2 REQUIRED)

target_include_directories(client PRIVATE
    ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(client
    ${SDL2_LIBRARIES}
)