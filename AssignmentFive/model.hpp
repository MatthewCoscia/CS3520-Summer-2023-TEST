#ifndef MODEL_HPP
#define MODEL_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ncurses.h>
#include <ctime>
#include "classes.hpp"

extern int array_height;
extern int array_width;

extern Animal*** main_array;

void generate_array(int doodlebug_amount, int queen_amount, int male_amount, int worker_amount);
void simulate_movement(Animal*** array);
std::pair<int, int> getRandomAdjacentPoint(int y, int x);
bool isAnimalPresent(int y, int x);
void swapItems(int y1, int x1, int y2, int x2);
void doodlebugEatAnt(int doodleY, int doodleX, int antY, int antX);
std::vector<std::pair<int, int>> getSixteenNeighborhood(int y, int x);
void checkIfAntStarved(int y, int x);
void checkIfDoodleBugStarved(int y, int x);
void spawnDoodleBugs(std::vector<std::pair<int, int>> open);
void spawnAnts(std::vector<std::pair<int, int>> open);
int generateRandomAnt();
void killQueen(int y, int x);
std::vector<std::pair<int, int>> getPossibleSpawnLocations(std::vector<std::pair<int, int>> bulk);
std::vector<std::pair<int, int>> getAllAdjacentPoints(int y, int x);

#endif // MODEL_HPP
