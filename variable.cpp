#include "includes/variable.h"

Variable::Variable(double value)
{
    this->value = value;
}

std::vector<double> Variable::evaluate()
{
    return std::vector<double> { value };
}

Variable make_variable(double value)
{
    return Variable(value);
}