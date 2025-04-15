#include <stdio.h>
#include <stdbool.h>

#define N_QUEENS 4

int board[N_QUEENS][N_QUEENS] = {{0}};

bool is_safe(int row, int col) {

    // check same column
    for (int i = row; i >= 0; i--) {
        if (board[i][col] == 1) {
            return false;
        }
    }

    // check top left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    // check top right diagonal
    for (int i = row, j = col; i >= 0 && j < N_QUEENS; i--, j++) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    return true;

}

void back_track(int row) {

    if (row == N_QUEENS) {
        for (int i = 0; i < N_QUEENS; i++) {
            for (int j = 0; j < N_QUEENS; j++) {
                printf("%d ", board[i][j]);
            }
            printf("\n");
        }
        printf("\n\n");
    }

    for (int j = 0; j < N_QUEENS; j++) {
        if (is_safe(row, j)) {
            board[row][j] = 1;
            back_track(row + 1);
            board[row][j] = 0;
        }
    }

}

int main() {
    back_track(0);
}
