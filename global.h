#ifndef GLOBAL_H_
#define GLOBAL_H_


#include "definition.h"
#include "memory_pool.h"
#include "state.h"
#include "tree_node.h"


class Global
{
public:
    static const int ME;
    static const int OPPONENT;

    static MemoryPool<State, sizeof(State) * 1024> state_pool;
    static MemoryPool<TreeNode, sizeof(TreeNode) * 1024> node_pool;
};


#endif // GLOBAL_H_
