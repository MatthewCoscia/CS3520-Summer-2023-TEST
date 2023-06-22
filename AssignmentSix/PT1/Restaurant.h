#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "Menu.h"
#include "Order.h"
#include "DeliveryPerson.h"
#include "Payment.h"

class Restaurant {
private:
    Menu menu;
    std::vector<Order> orders;
    std::vector<DeliveryPerson> delivery;
    Payment payment;

public:
    void publishMenu();
    void manageOrders();
    void manageDeliveryOptions();
    void handlePayments();
};

#endif

