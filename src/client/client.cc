#include "../../includes/client.hh"

#include <iostream>
#include <bits/random.h>
#include <nlohmann/json.hpp>

// for convenience
using json = nlohmann::json;



void Client::run()
{
    sf::TcpSocket socket;
    bool done = false;
    sf::Socket::Status status = socket.connect("0.0.0.0", port);
    if (status != sf::Socket::Done)
    {
        std::cout << "Error connect" << std::endl;
    }
    sf::Packet receivePacket;

    std::string commands[9] = {"right", "left", "fwd", "leftfwd", "rightfwd", "jump", "back", "inspect", "me"};

    std::string command = "";
    std::string nextCommand = "";
    std::string response;
    while (!done)
    {

        sf::Packet receivePacket;

        if (socket.receive(receivePacket) == sf::Socket::Done)
        {
            receivePacket >> response;
            displayResponse(response);
        }
        else if (socket.receive(receivePacket) == sf::Socket::Disconnected)
        {
            break;
        }


        searchCommand(response, command, nextCommand);
        sf::Packet sendPacket;
        sendPacket << commands[generateRandNum(0,8)];
        socket.send(sendPacket);
        sf::Packet sendPacket2;
        sendPacket2 << nextCommand;
        if (nextCommand != "")
            socket.send(sendPacket2);
    }
}

void Client::searchCommand(std::string mapResponse, std::string &command, std::string& nextCommand) {
    if (mapResponse == "") {return;}
    json j;
    if (mapResponse[2] != 'i') {
        j = json::parse(mapResponse);
    }

    std::vector<std::string> leftRightFwd = {"fwd","fwd","fwd", "leftfwd", "rightfwd\n", "inspect\n"};
    std::vector<std::string> leftRight = {"left", "right", "right\n"};
    std::vector<std::string> attacks = {"fwd", "fwd", "leftfwd\n", "rightfwd\n"};
    if (j["map"] != nullptr) {
        if (j["map"][1] == "D") {
            int i = generateRandNum(0,2);
            command = leftRight[i];
            nextCommand = "me\n";
        }
        else if (j["map"][2] == "M" || j["map"][2] == "L" || j["map"][2] == "S") {
            command = "fwd\n";
            nextCommand = "right\n";
        }
        else if (j["map"][0] == "M" || j["map"][0] == "L" || j["map"][0] == "S") {
            command = "fwd\n";
            nextCommand = "left\n";
        }
        else if (j["map"][1] == " ") {
            int i = generateRandNum(0,5);
            command = leftRightFwd[i];
            nextCommand = "me\n";
        }
        else if (j["map"][1] == "M" || j["map"][1] == "L" || j["map"][1] == "S" )  {
            command = "fwd\n";
        }
        else if(isdigit(j["map"][1].get<std::string>()[0])) {
            int i = generateRandNum(0,3);
            command = attacks[i];
            nextCommand = "me\n";
        }
    }
    else {
        if (j[command] == "KO") {
            int i = generateRandNum(0,2);
            command = leftRight[i];
        }
        else {
            command = "";
            nextCommand = "";
        }
    }
}

int Client::generateRandNum(int min, int max)
{
    std::random_device seed;
    std::mt19937 rng(seed());
    std::uniform_int_distribution<int> gen(min, max); // uniform, unbiased

    return gen(rng);
}

void Client::displayResponse(std::string response) {
    if (response == "") {return;}
    json j;
    if (response[2] != 'i') {
        j = json::parse(response);
    }
    if (j["map"] == nullptr)
        std::cout << response << std::endl;
    else {
        std::cout << "{\"map\":" << std::endl;
        std::cout << "                 [";
        for (size_t i  = 0; i < j["map"].size(); i++) {
            std::cout<<j["map"][i];
            if (i != j["map"].size() - 1){
                std::cout << " ,";
            }
        }
        std::cout<<"]"<<std::endl;
        std::cout << "}" << std::endl;
    }
}
