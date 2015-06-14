#include "state.h"

#include "global.h"


State::State(int M, int N, int** board_, const int* top_)
    : M(M), N(N)
{
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = board_[i][j];
        }
    }
    for (int j = 0; j < N; j++) {
        top[j] = top_[j];
    }
}


State::~State()
{
}


state_ptr State::create_state(const State& state)
{
    return state_ptr(Global::state_pool.newElement(state), [](State* p){
        Global::state_pool.deleteElement(p);
    });
}


void State::move(int x, int y, int candidate)
{
    board[x][y] = candidate;
    top[y] = x;
}
