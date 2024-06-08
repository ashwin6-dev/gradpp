#include "includes/ops.h"
#include <cassert>
#include <iostream>

BinOp::BinOp(Node* left, Node* right) 
{
    this->left = left;
    this->right = right;
    dependencies.push_back(left);
    dependencies.push_back(right);
}

double Add::evaluate()
{
    return left->evaluate() + right->evaluate();
}

Node* Add::partial(Node* incoming_gradient, Node* wrt)
{
    if (this==wrt)
        return incoming_gradient;

    Node* left_partial = left->partial(incoming_gradient, wrt);

    if (left_partial != nullptr)
        return left_partial;

    return right->partial(incoming_gradient, wrt);
}

Add* add(Node* left, Node* right)
{
    return new Add(left, right);
}