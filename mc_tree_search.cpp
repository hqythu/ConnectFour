#include "mc_tree_search.h"

#include <cmath>
#include <list>
#include <random>

#include <conio.h>
#include <atlstr.h>

using std::list;
using std::shared_ptr;
using std::unique_ptr;
using std::make_shared;
using std::make_pair;


MCTreeSearch::MCTreeSearch(int M, int N, rule_ptr rule)
    : M(M), N(N), rule(rule)
{
    
}


MCTreeSearch::~MCTreeSearch()
{
}


point MCTreeSearch::solve(const State& state)
{
    root = TreeNode::create_node(0, 0, Global::ME);
    int times = 100000;

    for (int k = 0; k < times; k++) {
        list<node_ptr> visited;
        node_ptr t = root;
        state_ptr s = State::create_state(state);
        int candidate = Global::ME;
        visited.push_back(root);
        while (!t->is_leaf()) {
            t = t->select();
            visited.push_back(t);
            auto move = t->get_move();
            s->move(move.first, move.second, candidate);
            candidate = candidate % 2 + 1;
        }
        t->expand(rule, s);
        node_ptr new_node = t->select();
        visited.push_back(new_node);
        auto move = new_node->get_move();
        s->move(move.first, move.second, candidate);
        int value = new_node->monte_carlo(rule, s);
        for (const auto& node : visited) {
            node->update(value);
        }
    }
    node_ptr selected = root->choose_best();
    auto move = selected->get_move();
    return make_pair(move.first, move.second);
}
