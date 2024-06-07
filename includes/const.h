#pragma once
#include "node.h"

class Const : public Node {
    double value;

public:
    Const(double value);
    std::vector<double> evaluate();
};

Const make_const(double variable);