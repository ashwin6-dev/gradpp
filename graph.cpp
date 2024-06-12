#include "includes/graph.h"
#include "includes/ops.h"
#include "includes/const.h"

#include <cassert>
#include <iostream>

Graph::Graph(std::vector<Placeholder*> placeholders)
{
    this->placeholders = placeholders;
}

void Graph::set_outputs(std::vector<Node*> outputs)
{
    this->outputs = outputs;
}

void Graph::set_grad_graph(bool is_grad)
{
    grad_graph = is_grad;
}

bool Graph::is_grad_graph()
{
    return grad_graph;
}

std::vector<Placeholder*> Graph::get_placeholders()
{
    return placeholders;
}

std::vector<Node*> Graph::get_outputs()
{
    return outputs;
}

std::vector<double> Graph::evaluate(std::vector<double> inputs)
{
    assert(inputs.size() == placeholders.size());
    
    for (int i = 0; i < inputs.size(); i++) {
        placeholders[i]->set_value(inputs[i]);
    }

    std::vector<double> results;
    int num_outputs = outputs.size();

    for (Node* output : outputs) {
        results.push_back(output->evaluate());
    }

    return results;
}

Graph Graph::partials()
{
    Const* c = make_const(1.0);
    std::vector<Node*> grad_outputs;    

    if (grad_graph) {
        assert(placeholders.size() == outputs.size());

        for (int i = 0; i < placeholders.size(); i++) {
            Placeholder* placeholder = placeholders[i];
            Node* output = outputs[i];

            Node* partial_output = make_const(0.0);
            Node* partial = output->partial(c, placeholder);
            partial_output = add(partial_output, partial);

            grad_outputs.push_back(partial_output);
        }

        Graph grad(placeholders);
        grad.set_outputs(grad_outputs);
        grad.set_grad_graph(true);

        return grad;
    }

    for (Placeholder* placeholder : placeholders) {
        Node* partial_output = make_const(0.0);
        for (Node* output : outputs) {
            Node* partial = output->partial(c, placeholder);
            partial_output = add(partial_output, partial);
        }

        grad_outputs.push_back(partial_output);
    }

    Graph grad(placeholders);
    grad.set_outputs(grad_outputs);
    grad.set_grad_graph(true);
        
    return grad;
}

Graph make_graph(std::vector<Placeholder*> placeholders)
{
    return Graph(placeholders);
}