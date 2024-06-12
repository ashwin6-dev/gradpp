#pragma once

#include "graph.h"
#include "node.h"
#include "jit.h"

#include <bits/stdc++.h>

typedef std::unordered_map<Node*, Register> register_allocation;

register_allocation allocate_registers(Graph graph);