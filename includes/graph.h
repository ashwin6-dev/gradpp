#pragma once

#include <vector>
#include "placeholder.h"

class Graph {
    bool grad_graph = false;
    std::vector<Placeholder*> placeholders;
    std::vector<Node*> outputs;

public:
    Graph(std::vector<Placeholder*> placeholders);
    void set_outputs(std::vector<Node*> outputs);
    std::vector<Placeholder*> get_placeholders();
    std::vector<double> evaluate(std::vector<double> inputs);
    Graph partials();
    void set_grad_graph(bool is_grad);
    bool is_grad_graph();
};

Graph make_graph(std::vector<Placeholder*> placeholders);