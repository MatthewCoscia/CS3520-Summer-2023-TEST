#ifndef PAYMENT_H
#define PAYMENT_H

#include "Order.h"
#include "Customer.h"
#include "Notification.h"

class Payment {
public:
    void processPayment(const Order& order);
    void validatePaymentDetails(const Customer& customer);
    void generateReceipt();
    void sendNotification();
};

#endif

