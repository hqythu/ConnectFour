#include <iostream>

#include "mc_tree_search.h"


int main()
{
    int M = 10, N = 10;
    int noX = 5, noY = 5;
    rule_ptr rule(new Rule(noX, noY));
    MCTreeSearch treesearch(M, N, rule);
    int** board = new int*[M];
    for (int i = 0; i < M; i++){
        board[i] = new int[N];
        for (int j = 0; j < N; j++){
            board[i][j] = 0;
        }
    }
    int* top = new int[N];
    for (int i = 0; i < N; i++) {
        top[i] = M;
    }
    State state(M, N, board, top);
    treesearch.solve(state);
    return 0;
}
