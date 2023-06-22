#ifndef ORDER_H
#define ORDER_H

#include "Dish.h"

class Order {
private:
    std::vector<Dish> dishes;

public:
    void addDish(const Dish& dish);
    void removeDish(const Dish& dish);
    float calculateTotalCost();
    void confirmOrder();
    void updateOrderStatus();
    void notifyCustomer();
};

#endif

