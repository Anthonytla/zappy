#include "client.hh"

#include <nlohmann/json.hpp>

// for convenience
using json = nlohmann::json;

Client::Client(std::string host, short int port)
{
    this->_host = host;
    this->_port = port;
}

void Client::connect()
{
    sf::TcpSocket socket;
    bool done = false;
    sf::Socket::Status status = socket.connect(this->_host, this->_port);
    if (status != sf::Socket::Done)
    {
        std::cout << "Error connect" << std::endl;
    }
    sf::Packet receivePacket;
    if (socket.receive(receivePacket) == sf::Socket::Done)
    {
        std::string ID;
        receivePacket >> ID;
        std::cout << ID << std::endl;
    }

    std::string commands[9] = {"right\n", "left\n", "fwd\n", "leftfwd\n", "rightfwd\n", "jump\n", "back\n", "inspect\n", "me\n"};

    std::string command = "";
    std::string nextCommand = "";
    std::string response;
    while (!done)
    {
        sf::Packet receivePacket;
        int n = 1;
        time_t start;
        start = time(0);
        
        
        start = start + n;

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
        sendPacket << command;
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
    
    std::vector<std::string> leftRightFwd = {"fwd\n","fwd\n","fwd\n", "leftfwd\n", "rightfwd\n", "inspect\n"};
    std::vector<std::string> leftRight = {"left\n", "right\n", "right\n"};
    std::vector<std::string> attacks = {"fwd\n", "fwd\n", "leftfwd\n", "rightfwd\n"};
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

bool Client::getArguments(int argc, char **argv) {
    for (int i = 1; i < argc; i += 2)
    {
        if (strcmp(argv[i], "--host") == 0)
        {
            _host = argv[i + 1];
        }
        else if (strcmp(argv[i], "--port") == 0)
        {
            try {
                _port = std::stoi(argv[i + 1]);
            }
            catch(std::invalid_argument& e) {
                std::cout << "Port must be an int" << std::endl;
                return false;
            }
        }
        else {
            std::cout << "Unknown option" << std::endl;
        }
    }
    return true;
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