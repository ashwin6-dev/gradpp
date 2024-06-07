#pragma once
#include "node.h"

class Variable : public Node {
    double value;

public:
    Variable(double value);
    std::vector<double> evaluate();
};

Variable make_variable(double variable);