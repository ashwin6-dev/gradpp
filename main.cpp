#include <iostream>
#include "includes/variable.h"
#include "includes/ops.h"
#include "includes/node-collection.h"

int main()
{
    Variable v1 = make_variable(10.0);
    Variable v2 = make_variable(10.0);
    Variable v3 = make_variable(5.0);
    Add a1 = add(&v1, &v2);
    Add a2 = add(&a1, &v3);
    
    NodeCollection c = make_collection(
        std::vector<Node*> { &a1, &a2 }
    );

    std::vector<double> result = (&c)->evaluate();

    std::cout << result[0] << std::endl;
    std::cout << result[1] << std::endl;

    return 0;
}