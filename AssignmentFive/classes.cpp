#include "classes.hpp"
#include "main.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ncurses.h>
#include <ctime>


void Animal::changeMoved(bool movedLocal) {
    moved = movedLocal;
}

void Animal::setStarve() {
    starve_count = 0;
}

void Animal::setBreed() {
    breed_count = 0;
}

void Animal::increaseBreed() {
    breed_count += 1;
}

int Animal::getStarvedInt() {
    return starve_count;
}

void Animal::increaseStarved() {
    starve_count += 1;
}

// Implementations for the member functions of Queen
char Queen::getSymbol() {
    return symbol;
}

int Queen::getXPos() {
    return xpos;
}

int Queen::getYPos() {
    return ypos;
}

void Queen::setPos(int YPos, int XPos) {
    xpos = XPos;
    ypos = YPos;
}

void Queen::move() {
    if (!moved && !fertilized) {
        pair<int, int> newpos = getRandomAdjacentPoint(ypos, xpos);
        int newY = newpos.first;
        int newX = newpos.second;
        if (!isAnimalPresent(newY, newX)) {
            swapItems(ypos, xpos, newY, newX);
            moved = true;
        }
    }
    if (fertilized) {
        breed_time_queen += 1;
    }
}

Queen::Queen(bool movedLocal) {
    moved = movedLocal;
}

void Queen::eat() {

}

void Queen::createOffspring() {
    if (breed_time_queen >= 30) {
        vector<pair<int, int>> temp = getSixteenNeighborhood(ypos, xpos);
        vector<pair<int, int>> open = getPossibleSpawnLocations(temp);
        if (open.size() >= 10) {
            spawnAnts(open);
            fertilized = false;
            breed_time_queen = 0;
            breed_cooldown = 15;
            cant_breed_time_queen = 0;
        }
        else {
            cant_breed_time_queen += 1;
        }
    }
    if (cant_breed_time_queen >= 30) {
        killQueen(ypos, xpos);
    }

}

void Queen::checkIfFertilized() {
    vector<pair<int, int>> temp = getAllAdjacentPoints(ypos, xpos);
    for (pair<int, int> i : temp) {
        int yCheck = i.first;
        int xCheck = i.second;
        if (main_array[yCheck][xCheck]->getSymbol() == 'O') {
            if (breed_cooldown == 0) {
                fertilized = true;
            }
            else {
                breed_cooldown -= 1;
            }
        }
    }
}

// Implementations for the member functions of Worker
char Worker::getSymbol() {
    return symbol;
}

int Worker::getXPos() {
    return xpos;
}

int Worker::getYPos() {
    return ypos;
}

void Worker::setPos(int YPos, int XPos) {
    xpos = XPos;
    ypos = YPos;
}

void Worker::move() {
    if (!moved) {
        pair<int, int> newpos = getRandomAdjacentPoint(ypos, xpos);
        int newY = newpos.first;
        int newX = newpos.second;
        if (!isAnimalPresent(newY, newX)) {
            swapItems(ypos, xpos, newY, newX);
            moved = true;
            this->setStarve();
        } else {
            this->increaseStarved();
            checkIfAntStarved(ypos, xpos);
        }
    }
}

Worker::Worker(bool movedLocal) {
    moved = movedLocal;
}

void Worker::eat() {

}

void Worker::createOffspring() {

}

void Worker::checkIfFertilized() {

}

// Implementations for the member functions of Male_Ant
char Male_Ant::getSymbol() {
    return symbol;
}

int Male_Ant::getXPos() {
    return xpos;
}

int Male_Ant::getYPos() {
    return ypos;
}

void Male_Ant::setPos(int YPos, int XPos) {
    xpos = XPos;
    ypos = YPos;
}

Male_Ant::Male_Ant(bool movedLocal) {
    moved = movedLocal;
}

void Male_Ant::move() {
    if (!moved) {
        pair<int, int> newpos = getRandomAdjacentPoint(ypos, xpos);
        int newY = newpos.first;
        int newX = newpos.second;
        cout << ypos << " " << newY << " " << xpos << " " << newX << "\n";
        if (!isAnimalPresent(newY, newX)) {
            swapItems(ypos, xpos, newY, newX);
            moved = true;
            this->setStarve();
        } else {
            this->increaseStarved();
            checkIfAntStarved(ypos, xpos);
        }
    }
}

void Male_Ant::eat() {

}

void Male_Ant::createOffspring() {

}

void Male_Ant::checkIfFertilized() {

}

// Implementations for the member functions of Doodlebug
char Doodlebug::getSymbol() {
    return symbol;
}

int Doodlebug::getXPos() {
    return xpos;
}

int Doodlebug::getYPos() {
    return ypos;
}

void Doodlebug::setPos(int YPos, int XPos) {
    xpos = XPos;
    ypos = YPos;
}

void Doodlebug::move() {
    if (!moved) {
        pair<int, int> newpos = getRandomAdjacentPoint(ypos, xpos);
        int newY = newpos.first;
        int newX = newpos.second;
        if (!isAnimalPresent(newY, newX)) {
            swapItems(ypos, xpos, newY, newX);
            moved = true;
        }
    }
}

void Doodlebug::eat() {
    bool ate = false;
    vector<pair<int, int>> adjacentPoints = getAllAdjacentPoints(ypos, xpos);
    for (pair<int, int> i : adjacentPoints) {
        if (main_array[i.first][i.second]->getSymbol() != 'X' && main_array[i.first][i.second]->getSymbol() != ' ') {
            doodlebugEatAnt(ypos, xpos, i.first, i.second);
            this->setStarve();
            ate = true;
            break;
        }
    }
    if (!ate) {
        this->increaseStarved();
        checkIfDoodleBugStarved(ypos, xpos);
    }
}

Doodlebug::Doodlebug(bool movedLocal) {
    moved = movedLocal;
}

void Doodlebug::createOffspring() {
    if (breed_count >= 10) {
        vector<pair<int, int>> temp = getSixteenNeighborhood(ypos, xpos);
        vector<pair<int, int>> open = getPossibleSpawnLocations(temp);
        if (open.size() >= 2) {
            spawnDoodleBugs(open);
            this->setBreed();
        }
    }
}

void Doodlebug::checkIfFertilized() {

}

// Implementations for the member functions of Empty
char Empty::getSymbol() {
    return symbol;
}

int Empty::getXPos() {
    return xpos;
}

int Empty::getYPos() {
    return ypos;
}

void Empty::setPos(int YPos, int XPos) {
    xpos = XPos;
    ypos = YPos;
}

void Empty::move() {

}

void Empty::eat() {

}

void Empty::createOffspring() {

}

void Empty::checkIfFertilized() {

}