#include "includes/node.h"

void Node::accept(Visitor* visitor)
{
    visitor->visit(this);
}

void Visitor::visit(Node* node)
{
    return;
}