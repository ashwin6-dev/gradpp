#include "includes/node-collection.h"
#include <cassert>
#include <iostream>

NodeCollection::NodeCollection(std::vector<Node*> collection)
{
    dependencies = collection;
}

std::vector<double> NodeCollection::evaluate()
{
    std::vector<double> result;

    for (Node* node : dependencies) {
        std::vector<double> node_result = node->evaluate();
        assert(node_result.size() == 1);
        result.push_back(node_result[0]);
    }

    return result;
}

NodeCollection make_collection(std::vector<Node*> collection)
{
    return NodeCollection(collection);
}