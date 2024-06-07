#pragma once

#include "node.h"

class BinOp : public Node {
    Node* left;
    Node* right;

public:
    BinOp(Node* left, Node* right);
};

class Add : public BinOp {
public:
    Add(Node* left, Node* right) : BinOp(left, right) {};
    void accept(Visitor* visitor);
};


Add add(Node* left, Node* right);