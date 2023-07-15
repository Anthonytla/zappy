#include "server.hh"
#include <cstring>
#include <string>

int main(int argc, char *argv[])
{
    Server *server = new Server();
    if (server->getArguments(argc, argv))
        server->run();
}
