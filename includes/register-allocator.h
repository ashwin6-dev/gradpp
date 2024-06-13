#pragma once

#include "graph.h"
#include "node.h"
#include "register.h"

#include <bits/stdc++.h>

typedef std::unordered_map<Node*, Register> register_allocation;

Register inc_reg(Register reg);
void allocate_registers(Graph graph, register_allocation &allocation);