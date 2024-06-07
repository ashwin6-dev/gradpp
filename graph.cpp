#include "includes/graph.h"
#include <cassert>

Graph::Graph(std::vector<Placeholder*> placeholders)
{
    this->placeholders = placeholders;
}

void Graph::set_outputs(std::vector<Node*> outputs)
{
    this->outputs = outputs;
}

std::vector<double> Graph::evaluate(std::vector<double> inputs)
{
    assert(inputs.size() == placeholders.size());

    for (int i = 0; i < inputs.size(); i++) {
        placeholders[i]->set_value(inputs[i]);
    }

    int num_outputs = outputs.size();
    std::vector<double> results(num_outputs);

    for (int i = 0; i < num_outputs; i++) {
        results[i] = outputs[i]->evaluate();
    }

    return results;
}

Graph make_graph(std::vector<Placeholder*> placeholders)
{
    return Graph(placeholders);
}