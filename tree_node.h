#ifndef TREENODE_H_

#include <list>
#include <memory>
#include <utility>

#include "global.h"
#include "state.h"
#include "rule.h"


class TreeNode
{
private:
    std::list<node_ptr, SingletonPool<node_ptr>> children;
    int n_visited;
    int n_value;
    int candidate;
    int x, y;

public:
    TreeNode();
    TreeNode(int x, int y, int candidate);
    ~TreeNode();
    static node_ptr create_node(int x, int y, int candidate);

    int get_value() { return n_value; }
    int get_visited() { return n_visited; }
    point get_move() { return std::make_pair(x, y); }

    bool is_leaf();
    void update(int visited, int value);
    node_ptr select();
    node_ptr choose_best();
    void expand(const rule_ptr& rule, const state_ptr& state);
    int monte_carlo(const rule_ptr& rule, const state_ptr& state);
};


#endif // TREENODE_H_
