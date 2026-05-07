#include <iostream>
#include <string>

// Your generated header
#include "2048/2048.h"

using namespace std;

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

int main() {
    string choice;

    while (true) {
        clearScreen();
        cout << "=================================================" << endl;
        cout << "             APCS PROJECT SHOWCASE               " << endl;
        cout << "=================================================" << endl;
        cout << "  [1] Play 2048 (Terminal Edition)               " << endl;
        cout << "  [2] Play Wordle [PLACEHOLDER]                  " << endl;
        cout << "  [3] Exit System                                " << endl;
        cout << "=================================================" << endl;
        cout << "Select a module to launch (1-3): ";

        cin >> choice;
        
        // CLEAR THE BUFFER: Toss any extra characters typed after the first word
        cin.clear();
        cin.ignore(10000, '\n');

        if (choice == "1") {
            play2048(); 
        } 
        else if (choice == "2") {
            clearScreen();
            cout << "[System] Wordle is currently under construction." << endl;
            cout << "Enter any character to return... ";
            string dummy; 
            cin >> dummy;
            cin.ignore(10000, '\n');
        }
        else if (choice == "3" || choice == "q" || choice == "Q") {
            cout << "Shutting down..." << endl;
            break;
        }
        else {
            cout << "Invalid input. Enter any character to try again... ";
            string dummy;
            cin >> dummy;
            cin.ignore(10000, '\n');
        }
    }

    return 0;
}