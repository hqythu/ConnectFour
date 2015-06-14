#include "rule.h"

#include <cstdlib>
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
    int j;
    do {
        j = rand() % N;
    } while (top[j] == 0 || (top[j] == 1 && no_x == 0 && no_y == j));
    int x = top[j] - 1, y = j;
    if (x == no_x && y == no_y) {
        x--;
    }
    return std::make_pair(x, y);
}


bool Rule::is_me_win(const state_ptr& state, int x, int y) const
{
    int M = state->get_M(), N = state->get_N();
    const State::board_t& board = state->get_board();
    //横向检测
    int i, j;
    int count = 0;
    for (i = y; i >= 0; i--)
        if (!(board[x][i] == 2))
            break;
    count += (y - i);
    for (i = y; i < N; i++)
        if (!(board[x][i] == 2))
            break;
    count += (i - y - 1);
    if (count >= 4) return true;

    //纵向检测
    count = 0;
    for (i = x; i < M; i++)
        if (!(board[i][y] == 2))
            break;
    count += (i - x);
    if (count >= 4) return true;

    //左下-右上
    count = 0;
    for (i = x, j = y; i < M && j >= 0; i++, j--)
        if (!(board[i][j] == 2))
            break;
    count += (y - j);
    for (i = x, j = y; i >= 0 && j < N; i--, j++)
        if (!(board[i][j] == 2))
            break;
    count += (j - y - 1);
    if (count >= 4) return true;

    //左上-右下
    count = 0;
    for (i = x, j = y; i >= 0 && j >= 0; i--, j--)
        if (!(board[i][j] == 2))
            break;
    count += (y - j);
    for (i = x, j = y; i < M && j < N; i++, j++)
        if (!(board[i][j] == 2))
            break;
    count += (j - y - 1);
    if (count >= 4) return true;

    return false;
}


bool Rule::is_opponent_win(const state_ptr& state, int x, int y) const
{
    int M = state->get_M(), N = state->get_N();
    const State::board_t& board = state->get_board();
    //横向检测
    int i, j;
    int count = 0;
    for (i = y; i >= 0; i--)
        if (!(board[x][i] == 1))
            break;
    count += (y - i);
    for (i = y; i < N; i++)
        if (!(board[x][i] == 1))
            break;
    count += (i - y - 1);
    if (count >= 4) return true;

    //纵向检测
    count = 0;
    for (i = x; i < M; i++)
        if (!(board[i][y] == 1))
            break;
    count += (i - x);
    if (count >= 4) return true;

    //左下-右上
    count = 0;
    for (i = x, j = y; i < M && j >= 0; i++, j--)
        if (!(board[i][j] == 1))
            break;
    count += (y - j);
    for (i = x, j = y; i >= 0 && j < N; i--, j++)
        if (!(board[i][j] == 1))
            break;
    count += (j - y - 1);
    if (count >= 4) return true;

    //左上-右下
    count = 0;
    for (i = x, j = y; i >= 0 && j >= 0; i--, j--)
        if (!(board[i][j] == 1))
            break;
    count += (y - j);
    for (i = x, j = y; i < M && j < N; i++, j++)
        if (!(board[i][j] == 1))
            break;
    count += (j - y - 1);
    if (count >= 4) return true;

    return false;
}


bool Rule::is_tie(const state_ptr& state) const
{
    int M = state->get_M(), N = state->get_N();
    const State::top_t& top = state->get_top();
    bool tie = true;
    for (int i = 0; i < N; i++)
    {
        if (!(top[i] == 0 || (top[i] == 1 && no_x == 0 && no_y == i)))
        {
            tie = false;
            break;
        }
    }
    return tie;
}
