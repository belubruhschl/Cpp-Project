#include <bits/stdc++.h>
#include <functional>
#include "2048/2048.h"

using namespace std;

void clearScreen() {
    cout << "\033[2J\033[1;1H"; //The ascii code to clear screen
}

class MainMenu {
private:
    struct MenuOption {
        string id;
        string description;
        function<void()> callback;
    };
    vector<MenuOption> options;

public:
    void addOption(const string& id, const string& description, function<void()> callback) {
        options.push_back({id, description, callback});
    }

    void show() {
        string choice;
        clearScreen();
        cout << "=================================================" << endl;
        cout << "            C++ Class Game App!                  " << endl;
        cout << "=================================================" << endl;
        
        for (const auto& opt : options) {
            cout << "  [" << opt.id << "] " << opt.description << endl;
        }
        cout << "=================================================" << endl;
        cout << "Select a module to launch: ";
        
        cin >> choice;

        bool found = false;
        for (const auto& opt : options) {
            if (opt.id == choice) {
                opt.callback();
                found = true;
                break;
            }
        }

        if (!found) {
            if (choice == "q" || choice == "Q") {
                cout << "Shutting down..." << endl;
            } else {
                cout << "Invalid input. " << endl;
            }
        }
    }
};

int main() {
    MainMenu menu;

    menu.addOption("1", "Play 2048 (Terminal Edition)", []() {
        play2048();
    });

    menu.addOption("2", "Play Wordle [PLACEHOLDER]", []() {
        clearScreen();
        cout << "Under development" << endl;
    });

    menu.addOption("3", "Neuron Network Training", []() {
        clearScreen();
        cout << "Under Development" << endl;
    });

    menu.addOption("4", "Exit System", []() {
        cout << "Shutting down..." << endl;
    });

    menu.show();

    return 0;
}