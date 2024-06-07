#include "includes/variable.h"

Variable::Variable(double value)
{
    this->value = value;
}

void Variable::accept(Visitor* visitor)
{
    visitor->visit(this);
}

Variable make_variable(double value)
{
    return Variable(value);
}