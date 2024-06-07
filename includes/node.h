#pragma once
#include <vector>

class Visitor;

class Node {
protected:
    std::vector<Node*> dependencies;

public:
    void accept(Visitor* visitor);
};

class Visitor {
public:
    void visit(Node* node);
};