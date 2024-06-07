#pragma once
#include <vector>

class Node {
protected:
    std::vector<Node*> dependencies;

public:
    virtual std::vector<double> evaluate();
};