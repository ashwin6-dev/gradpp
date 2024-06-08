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
    double evaluate();
    Node* partial(Node* incoming_gradient, Node* wrt);
};


Add* add(Node* left, Node* right);

class Sub : public BinOp {
public:
    Sub(Node* left, Node* right) : BinOp(left, right) {};
    double evaluate();
    Node* partial(Node* incoming_gradient, Node* wrt);
};


Sub* sub(Node* left, Node* right);

class Mul : public BinOp {
public:
    Mul(Node* left, Node* right) : BinOp(left, right) {};
    double evaluate();
    Node* partial(Node* incoming_gradient, Node* wrt);
};


Mul* mul(Node* left, Node* right);