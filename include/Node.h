//
// Created by antho on 01/09/24.
//

#ifndef NODE_H
#define NODE_H
#include <string>
#include <vector>
#include <nlohmann/json.hpp>


class Node {
    public:
    Node(std::string name);

    private:
    std::string name;
    std::string command;
    std::vector<Node*> children;
};





#endif //NODE_H
