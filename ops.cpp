#include "includes/ops.h"

BinOp::BinOp(Node* left, Node* right) 
{
    this->left = left;
    this->right = right;
    dependencies.push_back(left);
    dependencies.push_back(right);
}

void Add::accept(Visitor* visitor)
{
    return visitor->visit(this);
}

Add add(Node* left, Node* right)
{
    return Add(left, right);
}