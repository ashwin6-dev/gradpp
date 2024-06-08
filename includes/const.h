#pragma once
#include "node.h"

class Const : public Node {
    double value;

public:
    Const(double value);
    double evaluate();
    Node* partial(Node* incoming_gradient, Node* wrt);
};

Const* make_const(double variable);