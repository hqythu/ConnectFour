#include "global.h"


const int Global::ME = 2;
const int Global::OPPONENT = 1;

MemoryPool<State, sizeof(State) * 1024> Global::state_pool;
MemoryPool<TreeNode, sizeof(TreeNode) * 1024> Global::node_pool;
