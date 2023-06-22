#ifndef DISH_H
#define DISH_H

class Dish {
private:
    std::string name;
    std::string description;
    float price;

public:
    // Constructors, getters, and setters for name, description, and price
    float calculateTotalCost();
    bool checkAvailability();
};

#endif

