#include "includes/const.h"

Const::Const(double value)
{
    this->value = value;
}

double Const::evaluate()
{
    return value;
}

Const make_const(double value)
{
    return Const(value);
}