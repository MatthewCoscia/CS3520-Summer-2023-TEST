#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account {
private:
    std::string username;
    std::string password;
    std::string contactDetails;

public:
    // Constructors, getters, and setters for username, password, and contactDetails
    void authenticate();
    void authorize();
    void sendNotification();
};

#endif

