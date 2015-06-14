#include "mc_tree_search.h"

#include <cmath>
#include <list>
#include <random>
#include <chrono>

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


point MCTreeSearch::solve(const State& state, int last_x, int last_y)
{
    root = TreeNode::create_node(last_x, last_y, Global::ME);
    const int times = 100000;
    const int monte_carlo_time = 5;

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
            if (rule->is_opponent_win(s, x, y)) {
                ternimate = true;
                value = 0;
            }
        }
        else {
            if (rule->is_me_win(s, x, y)) {
                ternimate = true;
                value = monte_carlo_time;
            }
        }
        if (rule->is_tie(s)) {
            ternimate = true;
            value = 0;
        }
        node_ptr new_node;
        if (!ternimate) {
            t->expand(rule, s);
            new_node = t->select();
            visited.push_back(new_node);
            auto move = new_node->get_move();
            s->move(move.first, move.second, candidate);
            value = 0;
            for (int i = 0; i < monte_carlo_time; i++) {
                value += new_node->monte_carlo(rule, s);
            }
        }
        for (const auto& node : visited) {
            node->update(monte_carlo_time, value);
        }
    }
    node_ptr selected = root->choose_best();
    auto move = selected->get_move();
    return make_pair(move.first, move.second);
}
