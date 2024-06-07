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

Add add(Node* left, Node* right)
{
    return Add(left, right);
}