cmake_minimum_required(VERSION 3.22.1)
project(Zappy)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(client)
include_directories(server)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -g -pedantic")
add_executable(Zappy
    src/server/main.cc
    src/server/server.cc
    includes/server.hh
    src/game_controller.cc
    includes/game_controller.hh
    src/game_model.cc
    includes/game_model.hh
    src/game_view.cc
    includes/game_view.hh
    src/gem.cc
    includes/gem.hh
    src/map.cc
    includes/map.hh
    src/player.cc
    includes/player.hh)
target_link_libraries(Zappy PRIVATE sfml-network sfml-system sfml-graphics sfml-window)

add_executable(client
    src/client/main.cc
    includes/client.hh
    src/client/client.cc
    src/DecisionTree.cpp
    includes/DecisionTree.h
    src/Node.cpp
    includes/Node.h
)
target_link_libraries(client PRIVATE sfml-network sfml-system)