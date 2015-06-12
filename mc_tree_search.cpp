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
    int times = 1 << 13;

    for (int k = 0; k < times; k++) {
        _cprintf("iter %d", k);
        list<node_ptr> visited;
        node_ptr t = root;
        state_ptr s = State::create_state(state);
        _cprintf(" create state");
        int candidate = Global::ME;
        while (!t->is_leaf()) {
            t = t->select();
            visited.push_back(t);
            auto move = t->get_move();
            s->move(move.first, move.second, candidate);
            candidate = candidate % 2 + 1;
        }
        _cprintf(" selected");
        t->expand(rule, s);
        _cprintf(" expanded");
        node_ptr new_node = t->select();
        _cprintf(" selected");
        visited.push_back(new_node);
        auto move = new_node->get_move();
        _cprintf(" %d %d", move.first, move.second);
        s->move(move.first, move.second, candidate);
        _cprintf(" moved");
        int value = new_node->monte_carlo(rule, s);
        for (const auto& node : visited) {
            node->update(value);
        }
        _cprintf(" updated");
        _cprintf("\n");
    }
    node_ptr selected = root->choose_best();
    auto move = selected->get_move();
    return make_pair(move.first, move.second);
}
