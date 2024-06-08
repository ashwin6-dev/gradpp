#include "includes/const.h"

Const::Const(double value)
{
    this->value = value;
}

double Const::evaluate()
{
    return value;
}

Node* Const::partial(Node* incoming_gradient, Node* wrt)
{
    return make_const(0.0);
}

Const* make_const(double value)
{
    return new Const(value);
}