#include <stdio.h>
#include <stdbool.h>

char board[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
int currentPlayer = 1; // Player 1 is X, Player 2 (AI) is O

void drawBoard() {
    printf("\nTic Tac Toe\n");
    printf("Player (X) - AI (O)\n\n");
    printf(" %c | %c | %c \n", board[0], board[1], board[2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[3], board[4], board[5]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[6], board[7], board[8]);
}

bool checkWin(char player) {
    int winConditions[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6}
    };

    for (int i = 0; i < 8; i++) {
        if (board[winConditions[i][0]] == player && 
            board[winConditions[i][1]] == player && 
            board[winConditions[i][2]] == player) {
            return true;
        }
    }
    return false;
}

bool isBoardFull() {
    for (int i = 0; i < 9; i++) {
        if (board[i] != 'X' && board[i] != 'O') {
            return false;
        }
    }
    return true;
}

int minimax(bool isMaximizing) {
    if (checkWin('O')) return 1;  // AI wins
    if (checkWin('X')) return -1; // Player wins
    if (isBoardFull()) return 0;   // Draw

    if (isMaximizing) {
        int bestScore = -1000;
        for (int i = 0; i < 9; i++) {
            if (board[i] != 'X' && board[i] != 'O') {
                board[i] = 'O'; // AI move
                int score = minimax(false);
                board[i] = '1' + i; // Reset
                bestScore = (score > bestScore) ? score : bestScore;
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int i = 0; i < 9; i++) {
            if (board[i] != 'X' && board[i] != 'O') {
                board[i] = 'X'; // Player move
                int score = minimax(true);
                board[i] = '1' + i; // Reset
                bestScore = (score < bestScore) ? score : bestScore;
            }
        }
        return bestScore;
    }
}

void aiMove() {
    int bestScore = -1000;
    int bestMove = -1;
    for (int i = 0; i < 9; i++) {
        if (board[i] != 'X' && board[i] != 'O') {
            board[i] = 'O'; // AI move
            int score = minimax(false);
            board[i] = '1' + i; // Reset
            if (score > bestScore) {
                bestScore = score;
                bestMove = i;
            }
        }
    }
    board[bestMove] = 'O'; // Make the best move
}

void playerMove() {
    int choice;
    do {
        printf("Player, enter your choice (1-9): ");
        scanf("%d", &choice);
        choice--; // Adjusting index for array
    } while (choice < 0 || choice >= 9 || (board[choice] == 'X' || board[choice] == 'O'));
    
    board[choice] = 'X';
}

int main() {
    while (true) {
        drawBoard(); // Draw the board

        playerMove(); // Player makes a move
        if (checkWin('X')) {
            drawBoard(); // Show final board
            printf("Player wins!\n");
            break;
        }
        if (isBoardFull()) {
            drawBoard(); // Show final board
            printf("It's a draw!\n");
            break;
        }

        aiMove(); // AI makes a move
        if (checkWin('O')) {
            drawBoard(); // Show final board
            printf("AI wins!\n");
            break;
        }
        if (isBoardFull()) {
            drawBoard(); // Show final board
            printf("It's a draw!\n");
            break;
        }
    }
    return 0;
}

