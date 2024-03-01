#define _CRT_SECURE_NO_WARNINGS
#define MAX_NUM 25
#include <stdio.h>
#include <string.h>

/*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
 ⠀⠀⠀⠀⠀⠀⢠⣤⣤⡀⠀⠀⢀⣤⣤⣤⣤⡀⠀⠀⢀⣤⣤⡄⠀⠀⠀⠀⠀⠀
 ⠀⠀⠀⠀⠀⠀⢸⣿⣿⡇⠀⠀⢸⣿⣿⣿⣿⡇⠀⠀⢸⣿⣿⡇⠀⠀⠀⠀⠀⠀
 ⠀⠀⠀⠀⠀⠀⢸⣿⣿⣧⣤⣤⣼⣿⣿⣿⣿⣧⣤⣤⣼⣿⣿⡇⠀⠀⠀⠀⠀⠀
 ⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀
 ⠀⠀⠀⠀⠀⠀⠀⠀⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⠀⠀⠀⠀⠀⠀⠀⠀
 ⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀
 ⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀
 ⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀
 ⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀
 ⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀
 ⠀⠀⠀⠀⠀⠀⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⠀⠀⠀⠀⠀⠀
 ⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
 ⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
 ⠀⠀⠀⠀⠀⠀⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠀⠀⠀⠀⠀⠀
 */

int BOARD[MAX_NUM][MAX_NUM]; // Chess board
int N; // Board size
int L; // Pieces to place
int K; // Already placed

// Checking if we can place the Rook here
int POS_CHECK(int BOARD[MAX_NUM][MAX_NUM], int N, int X, int Y) {
    for (int i = 0; i < N; i++) {
        if (BOARD[X][i] == 1 || BOARD[i][Y] == 1) {
            return 1;
        }
    }
    return 0;
}

// Placing the Rooks and outputing the answers
void FIND_SOLUTIONS(int BOARD[MAX_NUM][MAX_NUM], int N, int L, int X, int Y) {
    if (L != 0) {
        for (int i = X; i < N; i++) {
            if (i > X) // Staying in array's bounds, switching to Y
                Y = 0;
            for (int j = Y; j < N; j++) {
                // Checking and cycling until all Rooks are placed
                if (BOARD[i][j] == 0 && (POS_CHECK(BOARD, N, i, j) == 0)) {
                    BOARD[i][j] = 1;
                    if (j == N - 1) {
                        FIND_SOLUTIONS(BOARD, N, L - 1, i + 1, 0);
                    }
                    else {
                        FIND_SOLUTIONS(BOARD, N, L - 1, i, Y + 1);
                    }
                    BOARD[i][j] = 0;
                }
            }
        }
    }
    else { // Outputing
        FILE* FIN = fopen("output.txt", "a");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (BOARD[i][j] == 1) {
                    fprintf(FIN, "(%d,%d) ", i, j);
                }
            }
        }
        fprintf(FIN, "\n");
        fclose(FIN);
    }
}

int main(int argc, const char* argv[]) {
    FILE* FIN = fopen("input.txt", "r"); // File with input
    fscanf(FIN, "%d %d %d", &N, &L, &K);
    FILE* OUT = fopen("output.txt", "w"); // File with output

    for (int i = 0; i < MAX_NUM; i++) { // Filling the board with 0
        for (int j = 0; j < MAX_NUM; j++) {
            BOARD[i][j] = 0;
        }
    }
    for (int i = 0; i < K; i++) { // Placing 1s for Rooks
        int X, Y;
        fscanf(FIN, "%d %d", &X, &Y);
        BOARD[X][Y] = 1;
    }

    FIND_SOLUTIONS(BOARD, N, L, 0, 0); // Outputing results

    OUT = fopen("output.txt", "r"); // Checking for results
    if (fgetc(OUT) == EOF) { // END OF FILE = no solutions
        OUT = fopen("output.txt", "w");
        fprintf(OUT, "no solutions");
    }

    fclose(FIN);
    fclose(OUT);
    return 0;
}