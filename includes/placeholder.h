#pragma once

#include "node.h"

class Placeholder : public Node {
    double value;
public:
    void set_value(double value);
    double evaluate();
};


Placeholder* make_placeholder();