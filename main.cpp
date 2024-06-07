#include <iostream>
#include "includes/variable.h"
#include "includes/ops.h"

int main()
{
    Variable v1 = make_variable(10.0);
    Variable v2 = make_variable(10.0);
    Add a1 = add(&v1, &v2);

    std::vector<double> result = (&a1)->evaluate();

    std::cout << result[0] << std::endl;

    return 0;
}