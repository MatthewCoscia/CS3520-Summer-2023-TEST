#include <iostream>
#include <vector>
#include <cstdlib>
#include <ncurses.h>
#include <ctime>
#include "classes.hpp"
#include "model.hpp"

using namespace std;

int main() {
    pair<int, int> temp = getRandomAdjacentPoint(25, 25);\
    cout << temp.first << " " << temp.second;
    return 0;
}
