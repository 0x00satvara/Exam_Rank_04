#include <stdio.h>
#include <stdlib.h>

void print_board(int *board, int n)
{
    for (int row = 0; row < n - 1; row++) {
        printf("%i ", board[row]);
    }
    printf("%i\n", board[n - 1]);
}

int is_safe(int board[], int n, int row, int col)
{
    for (int i = 0; i < row; i++)
        if (board[i] == col)
            return (0);

    for (int i = row, j = col; j >= 0 && i >= 0; i--, j--)
        if (board[i] == j)
            return (0);

    for (int i = row, j = col; j < n && i >= 0; i--, j++)
        if (board[i] == j)
            return (0);

    return (1);
}

void solve_nqueens(int board[], int n, int row)
{
    if (row == n) {
        print_board(board, n);
        return;
    }

    for (int col = 0; col < n; col++) {
        if (is_safe(board, n, row, col)) {
            board[row] = col;
            solve_nqueens(board, n, row + 1);
            board[row] = -1;
        }
    }
}

int main(int ac, char *av[])
{
    if (ac != 2)
        return (0);

    int n = atoi(av[1]);

    int *board = malloc(sizeof(int) * n);
    if (!board)
        return (1);

    for (int y = 0; y < n; y++)
        board[y] = -1;

    solve_nqueens(board, n, 0);
    free(board);
}