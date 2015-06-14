#include "tree_node.h"

#include <cmath>
#include <cstdlib>
#include <random>
#include <limits>

MemoryPool<TreeNode> node_pool;


TreeNode::TreeNode()
{
}


TreeNode::TreeNode(int x, int y, int candidate)
{
    this->x = x;
    this->y = y;
    this->candidate = candidate;
    n_value = 0;
    n_visited = 0;
}


TreeNode::~TreeNode()
{
}


node_ptr TreeNode::create_node(int x, int y, int candidate)
{
    return node_ptr(node_pool.newElement(x, y, candidate), [](TreeNode* p) {
        node_pool.deleteElement(p);
    });
}


bool TreeNode::is_leaf()
{
    return children.size() == 0;
}


void TreeNode::update(int visited, int value)
{
    n_visited += visited;
    n_value += value;
}


node_ptr TreeNode::select()
{
    node_ptr selected;
    double max = -std::numeric_limits<double>::max();

    auto calc = [this](const node_ptr& child) {
        double epsilon = 1e-3;
        double result;
        if (this->candidate == Global::ME) {
            result = static_cast<double>(child->n_value) / (child->n_visited + epsilon)
                + sqrt(log(this->n_visited + 1) / (child->n_visited + epsilon))
                + rand() % 100 * epsilon / 100;
        }
        else {
            result = static_cast<double>(child->n_visited - child->n_value) / (child->n_visited + epsilon)
                + sqrt(log(this->n_visited + 1) / (child->n_visited + epsilon))
                + rand() % 100 * epsilon / 100;
        }
        return result;
    };

    for (const auto& child : children) {
        double uct = calc(child);
        if (uct > max) {
            selected = child;
            max = uct;
        }
    }
    return selected;
}


node_ptr TreeNode::choose_best()
{
    node_ptr selected;
    double max = -std::numeric_limits<double>::max();
    std::uniform_real_distribution<double> uniform(0, 1);

    auto calc = [this, &uniform](const node_ptr& child) {
        double epsilon = 1e-3;
        return static_cast<double>(child->n_value) / (child->n_visited + epsilon);
    };

    for (const auto& child : children) {
        double uct = calc(child);
        if (uct > max) {
            selected = child;
            max = uct;
        }
    }
    return selected;
}


void TreeNode::expand(const rule_ptr& rule, const state_ptr& state)
{
    auto move_list = rule->get_all_move(state);
    for (const auto& move : move_list) {
        int x = move.first, y = move.second;
        auto new_node = create_node(x, y, candidate % 2 + 1);
        children.push_back(new_node);
    }
}


int TreeNode::monte_carlo(const rule_ptr& rule, const state_ptr& state)
{
    state_ptr new_state = State::create_state(*state);
    int candidate = this->candidate;
    int k = 0;
    int x = this->x, y = this->y;
    while (true) {
        if (candidate == Global::ME) {
            if (rule->is_opponent_win(new_state, x, y)) {
                return 0;
            }
        }
        else {
            if (rule->is_me_win(new_state, x, y)) {
                return 1;
            }
        }
        if (rule->is_tie(new_state)) {
            return 0;
        }
        auto move = rule->get_random_move(new_state);
        x = move.first, y = move.second;
        new_state->move(x, y, candidate);
        candidate = candidate % 2 + 1;
        k++;
    }
}