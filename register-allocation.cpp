#include "includes/register-allocator.h"

register_allocation allocate_registers(Node* node)
{
    register_allocation allocation;
    Register start_reg = XMM0;

    for (Node* dependency : node->get_dependencies()) {
        
    }
}