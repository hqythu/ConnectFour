#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <random>
#include <memory>
#include <utility>

#include "memory_pool.h"
#include "singleton_pool.h"

class TreeNode;
class MCTreeSearch;
class State;
class Rule;

typedef std::shared_ptr<TreeNode> node_ptr;
typedef std::shared_ptr<State> state_ptr;
typedef std::shared_ptr<Rule> rule_ptr;

typedef std::pair<int, int> point;


class Global
{
public:
    static const int ME;
    static const int OPPONENT;

    //static MemoryPool<State> state_pool;
    //static MemoryPool<TreeNode> node_pool;
};


#endif // GLOBAL_H_
