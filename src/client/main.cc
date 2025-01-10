#include "client.hh"

int main(int argc, char *argv[]) {
    if (argc != 2) {return 0;}
    Client client(std::stoi(argv[1]));
    client.run();
}