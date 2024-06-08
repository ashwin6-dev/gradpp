#include "includes/ops.h"
#include "includes/const.h"
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
    Node* right_partial = right->partial(incoming_gradient, wrt);
    return add(left_partial, right_partial);
}

Add* add(Node* left, Node* right)
{
    return new Add(left, right);
}

double Sub::evaluate()
{
    return left->evaluate() - right->evaluate();
}

Node* Sub::partial(Node* incoming_gradient, Node* wrt)
{
    if (this==wrt)
        return incoming_gradient;

    Node* left_partial = left->partial(incoming_gradient, wrt);
    Node* right_incoming = mul(make_const(-1), incoming_gradient);
    Node* right_partial = right->partial(right_incoming, wrt);
    return add(left_partial, right_partial);
}

Sub* sub(Node* left, Node* right)
{
    return new Sub(left, right);
}

double Mul::evaluate()
{
    return left->evaluate() * right->evaluate();
}

Node* Mul::partial(Node* incoming_gradient, Node* wrt)
{
    if (this==wrt)
        return incoming_gradient;

    
    Node* left_incoming = mul(right, incoming_gradient);
    Node* left_partial = left->partial(left_incoming, wrt);
    Node* right_incoming = mul(left, incoming_gradient);
    Node* right_partial = right->partial(right_incoming, wrt);

    return add(left_partial, right_partial);
}

Mul* mul(Node* left, Node* right)
{
    return new Mul(left, right);
}