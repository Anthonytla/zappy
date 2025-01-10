cmake_minimum_required(VERSION 3.22.1)
project(Zappy)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(client)
include_directories(server)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -g -pedantic")
add_executable(Zappy
    server/main.cc
    server/server.cc
    server/server.hh
    game_controller.cc
    game_controller.hh
    game_model.cc
    game_model.hh
    game_view.cc
    game_view.hh
    gem.cc
    gem.hh
    map.cc
    map.hh
    player.cc
    player.hh)
target_link_libraries(Zappy PRIVATE sfml-network sfml-system sfml-graphics sfml-window)

add_executable(client
    client/main.cc
    client/client.hh
    client/client.cc
        DecisionTree.cpp
        DecisionTree.h
        Node.cpp
        Node.h
)
target_link_libraries(client PRIVATE sfml-network sfml-system)