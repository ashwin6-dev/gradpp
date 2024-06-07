#include "includes/const.h"

Const::Const(double value)
{
    this->value = value;
}

void Const::accept(Visitor* visitor)
{
    visitor->visit(this);
}

Const make_const(double value)
{
    return Const(value);
}