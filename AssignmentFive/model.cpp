//
// Created by matthewcoscia on 6/12/23.
//
#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>
#include <ncurses.h>
#include <ctime>
#include <thread>
#include <algorithm>
#include "model.hpp"
#include "classes.hpp"

int array_height = 50;
int array_width = 50;

Animal*** main_array;

using namespace std;

void generate_array(int doodlebug_amount, int queen_amount, int male_amount, int worker_amount ) {
    main_array = new Animal**[array_height];
    for (int y = 0; y < array_height; y++) {
        main_array[y] = new Animal*[array_width];
        for (int x = 0; x < array_width; x++) {
            main_array[y][x] = new Empty;
        }
    }

    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < doodlebug_amount; i++) {
        int x = rand() % array_width;  // Generate random x within valid range
        int y = rand() % array_height; // Generate random y within valid range
        delete main_array[y][x];            // Delete existing object if any
        main_array[y][x] = new Doodlebug(false);
        main_array[y][x]->setPos(y, x);
    }
    for (int i = 0; i < queen_amount; i++) {
        int x = rand() % array_width;  // Generate random x within valid range
        int y = rand() % array_height; // Generate random y within valid range
        delete main_array[y][x];            // Delete existing object if any
        main_array[y][x] = new Queen(false);
        main_array[y][x]->setPos(y, x);
    }
    for (int i = 0; i < male_amount; i++) {
        int x = rand() % array_width;  // Generate random x within valid range
        int y = rand() % array_height; // Generate random y within valid range
        delete main_array[y][x];            // Delete existing object if any
        main_array[y][x] = new Male_Ant(false);
        main_array[y][x]->setPos(y, x);
    }
    for (int i = 0; i < worker_amount; i++) {
        int x = rand() % array_width;  // Generate random x within valid range
        int y = rand() % array_height; // Generate random y within valid range
        delete main_array[y][x];            // Delete existing object if any
        main_array[y][x] = new Worker(false);
        main_array[y][x]->setPos(y, x);
    }
	
}

bool isAnimalPresent(int y, int x) {
    if (main_array[y][x]->getSymbol() != ' ') {
        return true;
    }
    else {
        return false;
    }
}

void simulate_movement() {
    for (int y = 0; y < array_height; y++) {
        for (int x = 0; x < array_width; x++) {
            main_array[y][x]->move();
        }
    }
}

void swapItems(int y1, int x1, int y2, int x2) {
        Animal* temp = main_array[y1][x1];
        main_array[y1][x1] = main_array[y2][x2];
        main_array[y2][x2] = temp;
        main_array[y1][x1]->setPos(y1, x1);
        main_array[y2][x2]->setPos(y2, x2);
}

void doodlebugEatAnt(int doodleY, int doodleX, int antY, int antX) {
    main_array[antY][antX] = new Empty;
    swapItems(doodleY, doodleX, antY, antX);
    main_array[antY][antX]->changeMoved(true);


}

void spawnDoodleBugs(vector<pair<int, int>> open) {
    vector<pair<int, int>> temp = open;
    random_shuffle(temp.begin(), temp.end());
    int y1 = temp[0].first;
    int y2 = temp[1].first;
    int x1 = temp[0].second;
    int x2 = temp[0].second;
    main_array[y1][x1] = new Doodlebug(false);
    main_array[y1][x1]->setPos(y1, x1);
    main_array[y1][x1]->setBreed();
    main_array[y1][x1]->setStarve();
    main_array[y2][x2] = new Doodlebug(false);
    main_array[y2][x2]->setPos(y2, x2);
    main_array[y2][x2]->setBreed();
    main_array[y2][x2]->setStarve();
}

int generateRandomAnt() {
    vector<int> numbers;
    for (int i = 1; i <= 100; ++i) {
        numbers.push_back(i);
    }
    random_device rd;
    mt19937 gen(rd());
    shuffle(numbers.begin(), numbers.end(), gen);
    return numbers[0];
}

void spawnAnts(vector<pair<int, int>> open) {
    vector<pair<int, int>> temp = open;
    random_shuffle(temp.begin(), temp.end());
    for (int i = 0; i < 10; ++i) {
        int tempY = temp[i].first;
        int tempX = temp[i].second;
        int antType = generateRandomAnt();
        if (antType >= 0 && antType <= 32) {
            main_array[tempY][tempX] = new Male_Ant(false);
            main_array[tempY][tempX]->setPos(tempY, tempX);
            main_array[tempY][tempX]->setStarve();
        }
        if (antType > 32 && antType <= 99) {
            main_array[tempY][tempX] = new Worker(false);
            main_array[tempY][tempX]->setPos(tempY, tempX);
            main_array[tempY][tempX]->setStarve();
        }
        if (antType == 100) {
            main_array[tempY][tempX] = new Worker(false);
            main_array[tempY][tempX]->setPos(tempY, tempX);
            main_array[tempY][tempX]->setBreed();
        }

    }
}

vector<pair<int, int>> getPossibleSpawnLocations(vector<pair<int, int>> bulk) {
    vector<pair<int, int>> open;
    for (pair<int, int> i : bulk) {
        if (!isAnimalPresent(i.first, i.second)) {
            open.push_back({i.first, i.second});
        }
    }
    return open;
}

vector<pair<int, int>> getSixteenNeighborhood(int y, int x) {
    vector<pair<int, int>> temp;
    int offsets[24][2] = {
            // The 8 neighboring points directly surrounding the cell (same as your example)
            {-1, -1}, {-1, 0}, {-1, 1},
            {0, -1},           {0, 1},
            {1, -1},  {1, 0},  {1, 1},

            // The additional 16 neighboring points in the 16th neighborhood
            {-2, -2}, {-2, -1}, {-2, 0}, {-2, 1}, {-2, 2},
            {-1, -2}, {-1, 2},
            {0, -2},           {0, 2},
            {1, -2},  {1, 2},
            {2, -2},  {2, -1}, {2, 0}, {2, 1}, {2, 2}
    };
    for (int i = 0; i < 24; ++i) {
        pair<int, int> temp_pair = {y + offsets[i][0], x + offsets[i][1]};
        if (temp_pair.first < 0 || temp_pair.first > array_height - 1 || temp_pair.second < 0 || temp_pair.second > array_width - 1) {
            continue;
        }
        else {
            temp.push_back(temp_pair);
        }
    }
    return temp;
}

void checkIfAntStarved(int y, int x) {
    if (main_array[y][x]->getStarvedInt() >= 5) {
        delete main_array[y][x];
        main_array[y][x] = new Empty;
        main_array[y][x]->setPos(y, x);
    }
}

void killQueen(int y, int x) {
    delete main_array[y][x];
    main_array[y][x] = new Empty;
    main_array[y][x]->setPos(y, x);
}

void checkIfDoodleBugStarved(int y, int x) {
    if (main_array[y][x]->getStarvedInt() >= 10) {
        delete main_array[y][x];
        main_array[y][x] = new Empty;
        main_array[y][x]->setPos(y, x);
    }
}

vector<pair<int, int>> getAllAdjacentPoints(int y, int x) {
    vector<pair<int, int>> temp;
    int offsets[8][2] = {
            {-1, -1}, {-1, 0}, {-1, 1},
            {0, -1},           {0, 1},
            {1, -1},  {1, 0},  {1, 1}
    };
    for (int i = 0; i < 8; ++i) {
        pair<int, int> temp_pair = {y + offsets[i][0], x + offsets[i][1]};
        if (temp_pair.first < 0 || temp_pair.first > array_height - 1 || temp_pair.second < 0 || temp_pair.second > array_width - 1) {
            continue;
        }
        else {
            temp.push_back(temp_pair);
        }
    }
    return temp;
}

pair<int, int> getRandomAdjacentPoint(int y, int x) {
    int offsets[8][2] = {
            {-1, -1}, {-1, 0}, {-1, 1},
            {0, -1},           {0, 1},
            {1, -1},  {1, 0},  {1, 1}
    };
    random_device rd;
    mt19937 gen(rd());
    shuffle(&offsets[0][0], &offsets[7][2], gen);
    int adjacentY = y + offsets[0][0];
    int adjacentX = x + offsets[0][1];

    // if y goes out of bounds bottom of array
    if (adjacentY > array_height - 1) {
        adjacentY = y;
        adjacentX = adjacentX + offsets[0][1];
    }
    // if y goes out of bounds top of array
    if (adjacentY < 0) {
        adjacentY = y;
        adjacentX = adjacentX + offsets[0][1];
    }
    // if x goes out of bounds right of array
    if (adjacentX > array_width - 1) {
        adjacentX = x;
        adjacentY = adjacentY + offsets[0][0];
    }
    // if x goes out of bounds left of array
    if (adjacentX < 0) {
        adjacentX = x;
        adjacentY = adjacentY + offsets[0][0];
    }


    if (adjacentY > array_height - 1) {
        adjacentY = array_height - 1;
    }
    if (adjacentX > array_width - 1) {
        adjacentX = array_width - 1;
    }
    if (adjacentY < 0) {
        adjacentY = 0;
    }
    if (adjacentX < 0) {
        adjacentX = 0;
    }

    return make_pair(adjacentY, adjacentX);

}
