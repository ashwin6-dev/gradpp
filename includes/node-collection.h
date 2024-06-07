#pragma once

#include "node.h"

class NodeCollection : public Node {
public:
    NodeCollection(std::vector<Node*> collection);
    std::vector<double> evaluate();
};

NodeCollection make_collection(std::vector<Node*> collection);