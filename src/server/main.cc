#include <thread>
#include <SFML/Window/Event.hpp>
#include "../game_model.hh"
#include "../game_view.hh"
#include "server.hh"
#include "../game_controller.hh"


int main(int argc, char *argv[]) {
    if (argc != 3) {return 0;}
    Model model = Model();
    View view = View();
    GameController gc(view, model);
    Server server(std::stoi(argv[1]), gc, std::stoi(argv[2]));
    server.run();

}
