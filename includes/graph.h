#pragma once

#include <vector>
#include "placeholder.h"

class Graph {
    std::vector<Placeholder*> placeholders;
    std::vector<Node*> outputs;

public:
    Graph(std::vector<Placeholder*> placeholders);
    void set_outputs(std::vector<Node*> outputs);
    std::vector<double> evaluate(std::vector<double> inputs);
};


Graph make_graph(std::vector<Placeholder*> placeholders);