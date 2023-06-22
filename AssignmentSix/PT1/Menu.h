#ifndef MENU_H
#define MENU_H

#include "Dish.h"

class Menu {
private:
    std::vector<Dish> dishes;

public:
    void addDish(const Dish& dish);
    void updateDish(const Dish& dish);
    void removeDish(const Dish& dish);
    void provideMenu();
};

#endif

