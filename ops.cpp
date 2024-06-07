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

std::vector<double> Add::evaluate()
{
    std::vector<double> left_result = left->evaluate();
    std::vector<double> right_result = right->evaluate();

    assert(left_result.size() == 1 && right_result.size() == 1);

    return std::vector<double> { left_result[0] + right_result[0] };
}

Add add(Node* left, Node* right)
{
    return Add(left, right);
}