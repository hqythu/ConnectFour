#ifndef STATE_H_
#define STATE_H_

#include "global.h"

const int BOARD_MAX = 12;


class State
{
public:
    State(int M, int N, int** board_, const int * top_);
    ~State();

    static state_ptr create_state(const State& state);

    typedef int board_t[BOARD_MAX][BOARD_MAX];
    typedef int top_t[BOARD_MAX];

    const board_t& get_board() const { return board; }
    const top_t& get_top() const { return top; }
    int get_M() const { return M; }
    int get_N() const { return N; }

    void move(int x, int y, int candidate);

private:
    int board[BOARD_MAX][BOARD_MAX];
    int top[BOARD_MAX];
    int M, N;
};


#endif // STATE_H_
