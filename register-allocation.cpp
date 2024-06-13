#include "includes/register-allocator.h"

Register inc_reg(Register reg)
{
    if (reg == XMM7)
        return XMM0;

    return static_cast<Register>(static_cast<int>(reg) + 1);
}

void allocate_registers(Node* node, register_allocation &allocation)
{
    if (allocation.count(node) == 0) {
        allocation[node] = XMM0;
    }

    Register node_reg = allocation[node];
    Register curr_reg = node_reg;

    for (Node* dependency : node->get_dependencies()) {
        bool is_allocated = allocation.count(dependency) != 0;
        if (!is_allocated) {
            allocation[dependency] = curr_reg;
            curr_reg = inc_reg(curr_reg);
        }
    }
}