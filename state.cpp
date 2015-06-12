#include "state.h"


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
    /*return state_ptr(state_pool.newElement(state), [](State* p){
        state_pool.deleteElement(p);
    });*/
    return state_ptr(new State(state));
}


void State::move(int x, int y, int candidate)
{
    board[x][y] = candidate;
    top[y] = x;
}


bool State::is_me_win(int x, int y) const
{
    //ºáÏò¼ì²â
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

    //×İÏò¼ì²â
    count = 0;
    for (i = x; i < M; i++)
        if (!(board[i][y] == 2))
            break;
    count += (i - x);
    if (count >= 4) return true;

    //×óÏÂ-ÓÒÉÏ
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

    //×óÉÏ-ÓÒÏÂ
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


bool State::is_opponent_win(int x, int y) const
{
    //ºáÏò¼ì²â
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

    //×İÏò¼ì²â
    count = 0;
    for (i = x; i < M; i++)
        if (!(board[i][y] == 1))
            break;
    count += (i - x);
    if (count >= 4) return true;

    //×óÏÂ-ÓÒÉÏ
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

    //×óÉÏ-ÓÒÏÂ
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


bool State::is_tie() const
{
    bool tie = true;
    for (int i = 0; i < N; i++)
    {
        if (top[i] > 0)
        {
            tie = false;
            break;
        }
    }
    return tie;
}