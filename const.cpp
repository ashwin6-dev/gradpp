#include "includes/const.h"

Const::Const(double value)
{
    this->value = value;
}

std::vector<double> Const::evaluate()
{
    return std::vector<double> { value };
}

Const make_const(double value)
{
    return Const(value);
}