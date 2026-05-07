#include <bits/stdc++.h>
#include "2048/2048.h"
using namespace std;

void clearScreen() {
    cout << "\033[2J\033[1;1H"; //The ascii code to clear screen
}

int main() {
        char choice;
        clearScreen();
        cout << "=================================================" << endl;
        cout << "            C++ Class Game App!                  " << endl;
        cout << "=================================================" << endl;
        cout << "  [1] Play 2048 (Terminal Edition)               " << endl;
        cout << "  [2] Play Wordle [PLACEHOLDER]                  " << endl;
        cout << "  [3] Neuron Network Training                    " << endl;
        cout << "  [4] Exit System                                " << endl;
        cout << "=================================================" << endl;
        cout << "Select a module to launch (1-3): ";
        cin >> choice;
        if (choice == '1') {
            play2048(); 
        } else if (choice == '2') {
            clearScreen();
            cout << "Under development";
        } else if (choice == '3'){
            clearScreen();
            cout << "Under Development";
        } else if (choice == '4' || choice == 'q' || choice == 'Q') {
            cout << "Shutting down..." << endl;
        } else {
            cout << "Invalid input. ";
        }
    return 0;
}