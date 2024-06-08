#include "includes/placeholder.h"

void Placeholder::set_value(double value)
{
    this->value = value;
}

double Placeholder::evaluate()
{
    return value;
}

Placeholder* make_placeholder()
{
    Placeholder* p = new Placeholder;
    return p;
}