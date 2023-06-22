#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Account.h"
#include "Order.h"
#include "Notification.h"

class Customer {
private:
    Account account;
    std::vector<Dish> favoriteDishes;
    std::vector<Order> orders;
    Notification notification;

public:
    void createAccount();
    void storeFavoriteDish(const Dish& dish);
    void placeOrder(const Order& order);
    void trackOrderStatus();
    void trackDelivery();
};

#endif

