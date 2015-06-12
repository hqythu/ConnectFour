#include "rule.h"

#include <random>


Rule::Rule(int noX, int noY)
    : no_x(noX), no_y(noY)
{
}


Rule::~Rule()
{
}


Rule::point_list Rule::get_all_move(const state_ptr& state) const
{
    point_list result;
    int M = state->get_M(), N = state->get_N();
    const State::board_t& board = state->get_board();
    const State::top_t& top = state->get_top();
    for (int i = 0; i < N; i++) {
        if (top[i] > 0) {
            int x = top[i] - 1;
            int y = i;
            if (x == no_x && y == no_y) {
                x--;
                if (x >= 0) {
                    result.push_back(std::make_pair(x, y));
                }
            }
            else {
                result.push_back(std::make_pair(x, y));
            }
        }
    }
    return result;
}

point Rule::get_random_move(const state_ptr& state) const
{
    int M = state->get_M(), N = state->get_N();
    const State::board_t& board = state->get_board();
    const State::top_t& top = state->get_top();
    std::uniform_int_distribution<int> uniform(0, N - 1);
    int j;
    do {
        j = uniform(Global::generator);
    } while (top[j] == 0 || (top[j] == 1 && no_x == 0 && no_y == j));
    int x = top[j] - 1, y = j;
    if (x == no_x && y == no_y) {
        x--;
    }
    return std::make_pair(x, y);
}
