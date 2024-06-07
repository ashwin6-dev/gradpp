#include <iostream>
#include "includes/graph.h"
#include "includes/ops.h"
#include "includes/placeholder.h"

int main()
{
    Placeholder p1 = make_placeholder();
    Placeholder p2 = make_placeholder();

    Graph g = make_graph(
        std::vector<Placeholder*>{ &p1, &p2 }
    );

    Add a1 = add(&p1, &p2);
    Add a2 = add(&p1, &a1);

    g.set_outputs(
        std::vector<Node*> { &a1, &a2 }
    );

    std::vector<double> result = g.evaluate(
        std::vector<double> { 15.0, 20.0 }
    );

    std::cout << result[0] << std::endl;
    std::cout << result[1] << std::endl;

    return 0;
}