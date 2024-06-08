#include "includes/node.h"

double Node::evaluate()
{
    return 0;
}

Node* Node::partial(Node* incoming_gradient, Node* wrt)
{
    if (this == wrt)
        return incoming_gradient;

    return nullptr;
}