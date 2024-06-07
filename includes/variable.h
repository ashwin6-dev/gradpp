#pragma once
#include "node.h"

class Variable : public Node {
    double value;

public:
    Variable(double value);
    void accept(Visitor* visitor);
};

Variable make_variable(double variable);