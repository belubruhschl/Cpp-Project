#include <bits/stdc++.h>
using namespace std;
int board[4][4];

void delay(int ms) {
    this_thread::sleep_for(chrono::milliseconds(ms));
}

void rotateBoard() {
    int n = 4;
    for (int i = 0; i < n / 2; i++) {
        for (int j = i; j < n - i - 1; j++) {
            int temp = board[i][j];
            board[i][j] = board[n - 1 - j][i];
            board[n - 1 - j][i] = board[n - 1 - i][n - 1 - j];
            board[n - 1 - i][n - 1 - j] = board[j][n - 1 - i];
            board[j][n - 1 - i] = temp;
        }
    }
}

bool slideLeft() {
    bool changed = false;
    for (int r = 0; r < 4; r++) {
        int tempRow[4] = {0};
        int pos = 0;
        
        for (int c = 0; c < 4; c++) {
            if (board[r][c] != 0) {
                tempRow[pos] = board[r][c];
                pos++;
            }
        }
        
        for (int i = 0; i < 3; i++) {
            if (tempRow[i] != 0 && tempRow[i] == tempRow[i + 1]) {
                tempRow[i] = tempRow[i] * 2;
                tempRow[i + 1] = 0;
                changed = true;
            }
        }

        int finalRow[4] = {0};
        pos = 0;
        
        for (int i = 0; i < 4; i++) {
            if (tempRow[i] != 0) {
                finalRow[pos] = tempRow[i];
                pos++;
            }
        }

        for (int c = 0; c < 4; c++) {
            if (board[r][c] != finalRow[c]) {
                changed = true;
            }
            board[r][c] = finalRow[c];
        }
    }
    return changed;
}

void addTile() {
    int empty[16][2];
    int count = 0;
    
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            if (board[r][c] == 0) {
                empty[count][0] = r;
                empty[count][1] = c;
                count++;
            }
        }
    }
    
    if (count > 0) {
        int i = rand() % count;
        if (rand() % 10 < 9) {
            board[empty[i][0]][empty[i][1]] = 2;
        } else {
            board[empty[i][0]][empty[i][1]] = 4;
        }
    }
}

void printBoard() {
    cout << "\033[2J\033[1;1H"; 
    cout << "=========================" << endl;
    cout << "       2048 ASCII        " << endl;
    cout << "=========================" << endl;
    for (int r = 0; r < 4; r++) {
        cout << "+----+----+----+----+" << endl;
        for (int c = 0; c < 4; c++) {
            if (board[r][c] == 0) {
                cout << "|    ";
            } else {
                cout << "| " << setw(2) << board[r][c] << " ";
            }
        }
        cout << "|" << endl;
    }
    cout << "+----+----+----+----+" << endl;
    cout << "(W/A/S/D) Move, (Q) Quit" << endl;
    cout << "Enter your move: ";
}

void play2048() {
    for(int r = 0; r < 4; r++) {
        for(int c = 0; c < 4; c++) {
            board[r][c] = 0;
        }
    }

    srand(time(0));
    addTile();
    addTile();

    string input;
    while (true) {
        printBoard();
        cin >> input;
        cin.clear();
        cin.ignore(1000,'\n');//clear buffer
        // Check 1: Did they type more than one character? (e.g. "wasd")
        if (input.length() > 1) {
            continue; // Skip the turn and ask again
        }
        char op = tolower(input[0]);
        // Check 2: Is it an invalid key? (e.g. 'x')
        if (op != 'w' && op != 'a' && op != 's' && op != 'd' && op != 'q') {
            cout << "\nWrong Input! You can only type (W/A/S/D) Move, (Q) Quit";
            delay(500);
            continue; // Skip the turn and ask again
        }
        if (op == 'q') {
            break; // Quit the game and return to the main menu cleanly
        }

        bool moved = false;
        
        if (op == 'a') {
            moved = slideLeft();
        } else if (op == 'w') {
            rotateBoard(); rotateBoard(); rotateBoard();
            moved = slideLeft();
            rotateBoard();
        } else if (op == 'd') {
            rotateBoard(); rotateBoard();
            moved = slideLeft();
            rotateBoard(); rotateBoard();
        } else if (op == 's') {
            rotateBoard();
            moved = slideLeft();
            rotateBoard(); rotateBoard(); rotateBoard();
        }

        if (moved) {
            addTile();
        }
    }
}