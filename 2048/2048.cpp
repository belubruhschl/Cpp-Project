#include <bits/stdc++.h>
#define CLEAR_SCREEN cout << "\033[2J\033[1;1H"; 
#define DARK_TXT "\033[38;2;119;110;101m" //Only 2 and 4
#define WHT_TXT  "\033[38;2;249;246;242m" 
#define RESET    "\033[0m"

using namespace std;

random_device rd; mt19937 gen(rd());
int maxTile = 2;
int board[4][4];
int current_free = 16; //Sorry for snake case. This is a bit too long for camel so I think snake would be better.
int canSpawn[16];
string COLORS[] = {
    "\033[38;2;249;246;242m", //Ok I know you can use WHT_TXT but this is more neat
    "\033[48;2;238;228;218m",
    "\033[48;2;237;224;200m",
    "\033[48;2;242;177;121m",
    "\033[48;2;245;149;99m",
    "\033[48;2;246;124;95m",
    "\033[48;2;246;94;59m",
    "\033[48;2;237;207;114m",
    "\033[48;2;237;204;97m",
    "\033[48;2;237;200;80m",
    "\033[48;2;237;197;63m",
    "\033[48;2;237;194;46m",
    "\033[48;2;60;58;50m"
};

int randint(int min, int max) { 
    uniform_int_distribution<> distr(min, max);
    return distr(gen);
}

void delay(int ms) {
    this_thread::sleep_for(chrono::milliseconds(ms));
}

void printBoard() {
    cout << "\n";
    for (int i = 0; i<4; i++) {
        cout << "|";
        for (int j = 0; j<4;j++) {
            int tileNum = board[i][j];
            int width = (int)log10(maxTile)+1;
            int tile = tileNum ? (int)log2(tileNum) : 0; //CPU heavy isn't it?
            cout << COLORS[(tile>12 ? 12 : tile)] << (tileNum < 8 ? DARK_TXT : WHT_TXT) << setw(width) << (tileNum ? to_string(tileNum) : " " ) << RESET << "|";
        }
        cout << endl;
    }
}
void left() {
    for (int i = 0; i < 4; i++) {
        int target = 0;
        for (int j = 0; j < 4; j++) {
            if (board[i][j] != 0) {
                swap(board[i][target], board[i][j]);
                target++;
            }
        }
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 0 && board[i][j] == board[i][j + 1]) {
                int merged = board[i][j]*=2;
                if (merged > maxTile) maxTile = merged;
                board[i][j + 1] = 0;
                current_free++;
            }
        }
        target = 0;
        for (int j = 0; j < 4; j++) {
            if (board[i][j] != 0) {
                swap(board[i][target], board[i][j]);
                target++;
            }
        }
    }
}

void right() {
    for (int i = 0; i < 4; i++) {
        int target = 3;
        for (int j = 3; j >= 0; j--) {
            if (board[i][j] != 0) {
                swap(board[i][target], board[i][j]);
                target--;
            }
        }
        for (int j = 3; j > 0; j--) {
            if (board[i][j] != 0 && board[i][j] == board[i][j - 1]) {
                int merged = board[i][j]*=2;
                if (merged > maxTile) maxTile = merged;
                board[i][j - 1] = 0;
                current_free++;
            }
        }
        target = 3;
        for (int j = 3; j >= 0; j--) {
            if (board[i][j] != 0) {
                swap(board[i][target], board[i][j]);
                target--;
            }
        }
    }
}

void up() {
    for (int j = 0; j < 4; j++) {
        int target = 0;
        for (int i = 0; i < 4; i++) {
            if (board[i][j] != 0) {
                swap(board[target][j], board[i][j]);
                target++;
            }
        }
        for (int i = 0; i < 3; i++) {
            if (board[i][j] != 0 && board[i][j] == board[i + 1][j]) {
                int merged = board[i][j]*=2;
                if (merged > maxTile) maxTile = merged;
                board[i + 1][j] = 0;
                current_free++;
            }
        }
        target = 0;
        for (int i = 0; i < 4; i++) {
            if (board[i][j] != 0) {
                swap(board[target][j], board[i][j]);
                target++;
            }
        }
    }
}

void down() {
    for (int j = 0; j < 4; j++) {
        int target = 3;
        for (int i = 3; i >= 0; i--) {
            if (board[i][j] != 0) {
                swap(board[target][j], board[i][j]);
                target--;
            }
        }
        for (int i = 3; i > 0; i--) {
            if (board[i][j] != 0 && board[i][j] == board[i - 1][j]) {
                int merged = board[i][j]*=2;
                if (merged > maxTile) maxTile = merged;
                board[i - 1][j] = 0;
                current_free++;
            }
        }
        target = 3;
        for (int i = 3; i >= 0; i--) {
            if (board[i][j] != 0) {
                swap(board[target][j], board[i][j]);
                target--;
            }
        }
    }
}

bool isDead() {
    //Basically trying out all neighbors :P
    if (current_free) return false; //Cause you need it to be 0 which is false so it actually check the thing at down
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == board[i][j+1]) return false;
        }
    }
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 3; i++) {
            if (board[i][j] == board[i+1][j]) return false;
        }
    }
    return true; 
}

void spawn() {
    int count = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) {
                canSpawn[count++] = i * 4 + j;
            }
        }
    }
    
     
    current_free = count;

    if (count > 0) {
        int choice = canSpawn[randint(0, count - 1)];
        board[choice / 4][choice % 4] = (randint(0, 9) == 0 ? 4 : 2);
        current_free--; 
    }
}

//Trying to keep things modulize here :) which I dont really do
void init() {
    for (int i = 0;i<16;i++) {canSpawn[i]=0;}
    for (int i = 0; i<4; i++) {
        for (int j = 0; j<4; j++) {
            board[i][j] = {0};
        }
    }
}

void play2048() {
    init();
    while (true) {
        CLEAR_SCREEN
        if (isDead()) { //aka if it is 0 it will return true
            cout << "You Lost!";
            delay(1000);
            break;
        }
        printBoard();
        cout << endl << "Enter your choice (WASD or Q to quit): ";
        char input;
        cin >> input;
        if (input == 'q') break;
        if (input != 'w' && input != 'a'  && input != 's'  && input != 'd') continue;
        if (input == 'w') up();
        if (input == 's') down();
        if (input == 'a') left();
        if (input == 'd') right();
        spawn();
    }
}