/*snake_hame.cpp -------
*
* Filename: snake_game.cpp
* Description:
* Author: Adeel Bhutta
* Maintainer:
* Created: Sat Sep 12 13:16:12 2022
* Last-Updated: September 12 16:51 2022
*
*/

/* Commentary:
*
*
*
*/

/* Change log:
*
*
*/

/*Copyright (c) 2022 Adeel Bhutta
*
* All rights reserved.
*
* Additional copyrights may follow
*/
#include "game.hpp"
#include <cstdlib>
#include <cstdio>
#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

bool compare(int a, int b) {
    return a > b;
}

int main(void){
    printf("thuoeou");
    cout << "Welcome to the Snake game!" << "\n";
    cout << "Your high scores are: " << "\n";
    fstream file;
    string line;
    vector<int> scores;
    file.open("scores.txt", ios::in);
    if (file.is_open()) {
        while(getline(file, line)) {
            int temp = stoi(line);
            scores.push_back(temp);
        }
    }
    file.close();
    sort(scores.begin(), scores.end(), compare);
    int counter = 0;
    for (int num : scores) {
        if (counter < 10) {
            cout << num << ", ";
        }
        counter += 1;
    }
    cout << "\n";
    cout << "Are you ready to start, type y to begin." << "\n";
    char input;
    cin >> input;
    while (input != 'y') {
        cin >> input;
    }
    game();
    printf("tuenao");
    return(0);
}
