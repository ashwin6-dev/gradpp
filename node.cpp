#include "includes/node.h"
#include "includes/const.h"

double Node::evaluate()
{
    return 0;
}

Node* Node::partial(Node* incoming_gradient, Node* wrt)
{
    if (this == wrt)
        return incoming_gradient;

    return make_const(0.0);
}

std::vector<Node*> Node::get_dependencies()
{
    return dependencies;
}