#include <iostream>
#include "main.h"

using namespace std;

int main() {
    string input;
    do {
        cout << "Press 1 for Dice, 2 for the PhishingScanner, 3 for the MazeGenerator, or exit to close." << "\n";
        cin >> input;
        cout << "\n";
        if (input == "1") {
            Dice();
        }
        if (input == "2") {
            PhishingScanner();
        }
        if (input == "3") {
            Maze();
        }
    } while (input != "exit");
    return 0;
}
