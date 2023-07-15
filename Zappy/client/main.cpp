#include "client.hh"
#include <cstring>
#include <string>

int main(int argc, char *argv[])
{
    Client *client = new Client();
    if (client->getArguments(argc, argv))
        client->connect();
}