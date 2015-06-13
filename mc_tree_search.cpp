#include "mc_tree_search.h"

#include <cmath>
#include <list>
#include <random>
#include <chrono>

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
    const int times = 100000;

    using namespace std::chrono;
    steady_clock::time_point t1 = steady_clock::now();
    typedef duration<int, std::milli> time_mili;

    for (int k = 0; k < times; k++) {
        if (k % 10000 == 0) {
            steady_clock::time_point t2 = steady_clock::now();
            time_mili time_used = duration_cast<time_mili>(t2 - t1);
            if (time_used.count() > 3000) {
                break;
            }
        }
        list<node_ptr, SingletonPool<node_ptr>> visited;
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
        int value;
        auto move = t->get_move();
        int x = move.first, y = move.second;
        bool ternimate = false;
        if (candidate == Global::ME) {
            if (s->is_opponent_win(x, y)) {
                ternimate = true;
                value = 0;
            }
            else if (s->is_tie()) {
                ternimate = true;
                value = 0;
            }
        }
        else {
            if (s->is_me_win(x, y)) {
                ternimate = true;
                value = 1;
            }
            else if (s->is_tie()) {
                ternimate = true;
                value = 0;
            }
        }
        node_ptr new_node;
        if (ternimate) {
            value = candidate == Global::ME ? 0 : 1;
        }
        else {
            t->expand(rule, s);
            new_node = t->select();
            visited.push_back(new_node);
            auto move = new_node->get_move();
            s->move(move.first, move.second, candidate);
            value = new_node->monte_carlo(rule, s);
        }
        for (const auto& node : visited) {
            node->update(1, value);
        }
    }
    node_ptr selected = root->choose_best();
    auto move = selected->get_move();
    return make_pair(move.first, move.second);
}
