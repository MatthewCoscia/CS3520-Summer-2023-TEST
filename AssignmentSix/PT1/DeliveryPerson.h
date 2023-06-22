#ifndef DELIVERYPERSON_H
#define DELIVERYPERSON_H

#include "Order.h"
#include "Address.h"
#include "Notification.h"

class DeliveryPerson {
private:
    std::vector<Order> assignedOrders;
    Location currentLocation;
    Notification notification;

public:
    void manageDeliveryRequests();
    void trackDeliveryStatus();
    void updateOrderStatus();
    void updateDeliveryStatus();
    void notifyCustomer();
};

#endif

