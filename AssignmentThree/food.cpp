/*food.cpp -------
*
* Filename: food.cpp
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

#include <cstdlib>
#include <ncurses.h>
#include <cstdbool>
#include "food.hpp"
#include <ctime>


//Create new food
Food* create_food(int x, int y, enum Type type, int charType){
    srand(time(NULL));
    Food* new_food = (Food*)malloc(sizeof(Food));
    new_food->x = x;
    new_food->y = y;
    if (type == Increase){
        if (charType % 2 == 0) {
            new_food->type = 'O';
        }
        if (charType % 2 == 1) {
            new_food->type = 'P';
        }
    }
    else if(type == Decrease){
        if (charType % 2 == 0) {
            new_food->type = 'X';
        }
        if (charType % 2 == 1) {
            new_food->type = 'Z';
        }
    }
    else if (type == Obstacle) {
        new_food->type = '*';
    }

    return new_food;
}

//Check if food exists at coordinates
bool food_exists(Food* foods, int x, int y){
    Food* temp = foods;
    while(temp){
        if(temp->x == x && temp->y == y)
            return true;
        temp = temp->next;
    }
    return false;
}

//Add new food to end of food list
void add_new_food(Food* foods, Food* new_food){
    if (foods->next == nullptr) {
        new_food->prev = foods;
        foods->next = new_food;
        return;
    }
    add_new_food(foods->next, new_food);
}


char food_type(Food* foods, int x, int y){
    Food* temp = foods;
    while(temp){
        if(temp->x == x && temp->y == y) {
            return temp->type;
        }
        temp = temp->next;
    }
    return 'N';
}

// remove an eaten food.
Food* remove_eaten_food(Food* foods, int x, int y) {
    if (foods == nullptr) {
        return foods;
    }
    if (foods->x == x && foods->y == y) {
        if (foods->type == '*') {
            return foods;
        }
        free(foods);
        foods = NULL;
        return foods;
    }
    else {
        remove_eaten_food(foods->next, x, y);
    }
}

// Display all the food
void draw_food (Food *foods)
{   Food* temp = foods;
    while(temp) {
        start_color();
        init_pair(2, COLOR_GREEN, COLOR_MAGENTA);
        attron(2);
        mvprintw(temp->y, temp->x, "%c", temp->type);
        temp = temp->next;
        attroff(2);
    }
}
