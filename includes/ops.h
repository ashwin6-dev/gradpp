#pragma once

#include "node.h"

class BinOp : public Node {
protected:
    Node* left;
    Node* right;

public:
    BinOp(Node* left, Node* right);
};

class Add : public BinOp {
public:
    Add(Node* left, Node* right) : BinOp(left, right) {};
    std::vector<double> evaluate();
};


Add add(Node* left, Node* right);