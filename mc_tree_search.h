#ifndef MCTREESEARCH_H_
#define MCTREESEARCH_H_

#include "global.h"
#include "tree_node.h"


class MCTreeSearch
{
private:
    int M, N;

    node_ptr root;
    rule_ptr rule;

public:
    MCTreeSearch(int M, int N, rule_ptr rule);
    ~MCTreeSearch();

    point solve(const State& state);
    int monte_carlo(const state_ptr& state);
};


#endif // MCTREESEARCH_H_
