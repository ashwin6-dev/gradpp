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

std::vector<Placeholder*> Graph::get_placeholders()
{
    return placeholders;
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
        if (output == nullptr)
            std::cout<<"dsndsn"<<std::endl;

        results.push_back(output->evaluate());
    }

    return results;
}

Graph Graph::partials()
{
    Const* c = make_const(1.0);
    std::vector<Node*> grad_outputs;    

    for (Placeholder* placeholder : placeholders) {
        Node* partial_output = nullptr;
        for (Node* output : outputs) {
            Node* partial = output->partial(c, placeholder);
            
            if (partial_output != nullptr) {
                partial_output = add(partial_output, partial);
            }else {
                partial_output = partial;
            }
        }

        grad_outputs.push_back(partial_output);
    }

    Graph grad(placeholders);
    grad.set_outputs(grad_outputs);
    
    return grad;
}

Graph make_graph(std::vector<Placeholder*> placeholders)
{
    return Graph(placeholders);
}