#include <bits/stdc++.h>
#include "../NN/ai_tools.cpp"
using namespace std;
#define CLEAR_SCREEN cout << "\033[2J\033[1;1H";
#define DARK_TXT "\033[38;2;119;110;101m" // Only 2 and 4
#define WHT_TXT "\033[38;2;249;246;242m"
#define RESET "\033[0m"

extern int getch(); // Too lazy to make a header for main.cpp
random_device rd;
mt19937 gen(rd());
int maxTile = 2;
int board[4][4];
int current_free = 16; // Sorry for snake case. This is a bit too long for camel so I think snake would be better.
int canSpawn[16];
int get_score = 0;
string COLORS[] = {
    "\033[38;2;249;246;242m", // Ok I know you can use WHT_TXT but this is more neat
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
    "\033[48;2;60;58;50m"};

int randint(int min, int max)
{
    uniform_int_distribution<> distr(min, max);
    return distr(gen);
}

void delay(int ms)
{
    this_thread::sleep_for(chrono::milliseconds(ms));
}

void printBoard()
{
    cout << "\n";
    for (int i = 0; i < 4; i++)
    {
        cout << "|";
        for (int j = 0; j < 4; j++)
        {
            int tileNum = board[i][j];
            int tile = tileNum ? (int)log2(tileNum) : 0; // CPU heavy isn't it?
            cout << COLORS[(tile > 12 ? 12 : tile)] << (tileNum < 8 ? DARK_TXT : WHT_TXT) << string(((to_string(maxTile).length() + 2) - (tileNum ? to_string(tileNum) : " ").length()) / 2, ' ') << (tileNum ? to_string(tileNum) : " ") << string((to_string(maxTile).length() + 2) - (tileNum ? to_string(tileNum) : " ").length() - (((to_string(maxTile).length() + 2) - (tileNum ? to_string(tileNum) : " ").length()) / 2), ' ') << RESET << "|";
        }
        cout << endl;
    }
}
void left()
{
    for (int i = 0; i < 4; i++)
    {
        int target = 0;
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] != 0)
            {
                swap(board[i][target], board[i][j]);
                target++;
            }
        }
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != 0 && board[i][j] == board[i][j + 1])
            {
                int merged = board[i][j] *= 2;
                get_score += merged;
                if (merged > maxTile)
                    maxTile = merged;
                board[i][j + 1] = 0;
                current_free++;
            }
        }
        target = 0;
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] != 0)
            {
                swap(board[i][target], board[i][j]);
                target++;
            }
        }
    }
}

void right()
{
    for (int i = 0; i < 4; i++)
    {
        int target = 3;
        for (int j = 3; j >= 0; j--)
        {
            if (board[i][j] != 0)
            {
                swap(board[i][target], board[i][j]);
                target--;
            }
        }
        for (int j = 3; j > 0; j--)
        {
            if (board[i][j] != 0 && board[i][j] == board[i][j - 1])
            {
                int merged = board[i][j] *= 2;
                get_score += merged;
                if (merged > maxTile)
                    maxTile = merged;
                board[i][j - 1] = 0;
                current_free++;
            }
        }
        target = 3;
        for (int j = 3; j >= 0; j--)
        {
            if (board[i][j] != 0)
            {
                swap(board[i][target], board[i][j]);
                target--;
            }
        }
    }
}

void up()
{
    for (int j = 0; j < 4; j++)
    {
        int target = 0;
        for (int i = 0; i < 4; i++)
        {
            if (board[i][j] != 0)
            {
                swap(board[target][j], board[i][j]);
                target++;
            }
        }
        for (int i = 0; i < 3; i++)
        {
            if (board[i][j] != 0 && board[i][j] == board[i + 1][j])
            {
                int merged = board[i][j] *= 2;
                get_score += merged;
                if (merged > maxTile)
                    maxTile = merged;
                board[i + 1][j] = 0;
                current_free++;
            }
        }
        target = 0;
        for (int i = 0; i < 4; i++)
        {
            if (board[i][j] != 0)
            {
                swap(board[target][j], board[i][j]);
                target++;
            }
        }
    }
}

void down()
{
    for (int j = 0; j < 4; j++)
    {
        int target = 3;
        for (int i = 3; i >= 0; i--)
        {
            if (board[i][j] != 0)
            {
                swap(board[target][j], board[i][j]);
                target--;
            }
        }
        for (int i = 3; i > 0; i--)
        {
            if (board[i][j] != 0 && board[i][j] == board[i - 1][j])
            {
                int merged = board[i][j] *= 2;
                get_score += merged;
                if (merged > maxTile)
                    maxTile = merged;
                board[i - 1][j] = 0;
                current_free++;
            }
        }
        target = 3;
        for (int i = 3; i >= 0; i--)
        {
            if (board[i][j] != 0)
            {
                swap(board[target][j], board[i][j]);
                target--;
            }
        }
    }
}

bool isDead()
{
    // Basically trying out all neighbors :P
    if (current_free)
        return false; // Cause you need it to be 0 which is false so it actually check the thing at down
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == board[i][j + 1])
                return false;
        }
    }
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            if (board[i][j] == board[i + 1][j])
                return false;
        }
    }
    return true;
}

void spawn()
{
    int count = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == 0)
            {
                canSpawn[count++] = i * 4 + j;
            }
        }
    }

    current_free = count;

    if (count > 0)
    {
        int choice = canSpawn[randint(0, count - 1)];
        board[choice / 4][choice % 4] = (randint(0, 9) == 0 ? 4 : 2);
        current_free--;
    }
}

// Trying to keep things modulize here :) which I dont really do
void init()
{
    for (int i = 0; i < 16; i++)
    {
        canSpawn[i] = 0;
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            board[i][j] = {0};
        }
    }
}

void play2048()
{
    init();
    spawn();
    int mode = 2;
    cout << "\n";
    cout << "Welcome to 2048! Enter 1 for AI training mode, 0 for human playing mode!" << endl;
    cout << "Your choice: ";
    while (mode > 1)
    {
        cin >> mode;
    }
    if (!mode)
    {
        while (true)
        {
            CLEAR_SCREEN
            if (isDead())
            { // aka if it is 0 it will return true
                delay(1000);
                cout << "輸了！" << "\n";
                delay(1000);
                break;
            }
            printBoard();
            cout << endl
                 << "請選擇 (WASD 或 Q 離開)： ";
            char input = tolower(getch());
            // cin >> input;
            int before[4][4];
            copy(&board[0][0], &board[0][0] + 16, &before[0][0]);
            if (input == 'q')
                break;
            if (input != 'w' && input != 'a' && input != 's' && input != 'd')
                continue;
            if (input == 'w')
                up();
            if (input == 's')
                down();
            if (input == 'a')
                left();
            if (input == 'd')
                right();
            if (!equal(&board[0][0], &board[0][0] + 16, &before[0][0]))
                spawn();
        }
    }
    else
    {
        CLEAR_SCREEN
        cout << "\nLooks like you want to train AI! Enter the rounds it should play: ";
        int rounds = 0;
        cin >> rounds;
        // We are going to make 4 NN each with 2 hidden layer and 1 final output layer
        int gamma = 0.95;
        // Left 0
        neuron h1_left(16, 0.01);
        neuron h2_left(16, 0.01);
        neuron y_left(2, 0.01);
        // Right 1
        neuron h1_right(16, 0.01);
        neuron h2_right(16, 0.01);
        neuron y_right(2, 0.01);
        // up 2
        neuron h1_up(16, 0.01);
        neuron h2_up(16, 0.01);
        neuron y_up(2, 0.01);
        // Down 3
        neuron h1_down(16, 0.01);
        neuron h2_down(16, 0.01);
        neuron y_down(2, 0.01);

        for (int i = 0; i < rounds; i++)
        {
            int choice = 0;
            bool first = true;
            float reward = 0;
            float prevScore = 0;
            float prevh1 = 0;
            float prevh2 = 0;
            while (true)
            {
                if (isDead())
                { // aka if it is 0 it will return true
                    delay(1000);
                    cout << "輸了！" << "\n";
                    delay(1000);
                    break;
                }
                CLEAR_SCREEN
                printBoard();
                vector<float> state_for_h1;
                vector<float> state_for_h2;
                for (int j = 0; j < 4; j++)
                {
                    for (int k = 0; k < 4; k++)
                    {
                        state_for_h1.push_back((float)board[j][k]);
                        state_for_h2.push_back((float)board[k][j]);
                    }
                }
#define h1(x) h1_##x.setInput(state_for_h1)
#define h2(x) h2_##x.setInput(state_for_h2)
#define y(x) y_##x.setInput({h1_##x.y_hat(false), h2_##x.y_hat(true)})
                h1(left);
                h2(left);
                y(left);
                h1(right);
                h2(right);
                y(right);
                h1(up);
                h2(up);
                y(up);
                h1(down);
                h2(down);
                y(down);
                float leftScore = y_left.y_hat(false);
                float rightScore = y_right.y_hat(false);
                float upScore = y_up.y_hat(false);
                float downScore = y_down.y_hat(false);
                if (!first)
                {
#define TRAIN1(x) y_##x.train(2 * (prevScore - target))
#define TRAIN2(x) h1_##x.train(2 * (prevScore - target) * prevh1)
#define TRAIN3(x) h2_##x.train(2 * (prevScore - target) * prevh2)

                    if (choice == 0)
                    {
                        float target = reward + gamma * leftScore;
                        TRAIN1(left);
                        TRAIN2(left);
                        TRAIN3(left);
                        h1(left);
                        h2(left);
                        y(left);
                        leftScore = y_left.y_hat(false);
                    }
                    else if (choice == 1)
                    {
                        float target = reward + gamma * rightScore;
                        TRAIN1(right);
                        TRAIN2(right);
                        TRAIN3(right);
                        h1(right);
                        h2(right);
                        y(right);
                        rightScore = y_right.y_hat(false);
                    }
                    else if (choice == 2)
                    {
                        float target = reward + gamma * upScore;
                        TRAIN1(up);
                        TRAIN2(up);
                        TRAIN3(up);
                        h1(up);
                        h2(up);
                        y(up);
                        upScore = y_up.y_hat(false);
                    }
                    else if (choice == 3)
                    {
                        float target = reward + gamma * downScore;
                        TRAIN1(down);
                        TRAIN2(down);
                        TRAIN3(down);
                        h1(down);
                        h2(down);
                        y(down);
                        downScore = y_down.y_hat(false);
                    }
                }
                else
                {
                    first = false;
                }
                reward = 0;
                int before[4][4];
                copy(&board[0][0], &board[0][0] + 16, &before[0][0]);
                if (downScore > upScore && downScore > leftScore && downScore > rightScore)
                {
                    down();
                    prevScore = downScore;
                    prevh1 = h1_down.y_hat(false);
                    prevh2 = h2_down.y_hat(true);
                    choice = 3;
                }
                else if (upScore > downScore && upScore > leftScore && upScore > rightScore)
                {
                    up();
                    prevScore = upScore;
                    prevh1 = h1_up.y_hat(false);
                    prevh2 = h2_up.y_hat(true);
                    choice = 2;
                }
                else if (leftScore > upScore && leftScore > downScore && leftScore > rightScore)
                {
                    left();
                    prevScore = leftScore;
                    prevh1 = h1_left.y_hat(false);
                    prevh2 = h2_left.y_hat(true);
                    choice = 0;
                }
                else if (rightScore > upScore && rightScore > leftScore && rightScore > downScore)
                {
                    right();
                    prevScore = rightScore;
                    prevh1 = h1_right.y_hat(false);
                    prevh2 = h2_right.y_hat(true);
                    choice = 1;
                }
                if (isDead())
                {
                    reward = -999;
                }
                reward = (!get_score ? -1 : reward + get_score);
                if (!equal(&board[0][0], &board[0][0] + 16, &before[0][0]))
                {
                    spawn();
                } else {
                    reward = -100;
                }
                get_score = 0;
            }
        }
    }
}
