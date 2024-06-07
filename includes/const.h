#pragma once
#include "node.h"

class Const : public Node {
    double value;

public:
    Const(double value);
    void accept(Visitor* visitor);
};

Const make_const(double variable);