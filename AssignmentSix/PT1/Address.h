#ifndef ADDRESS_H
#define ADDRESS_H

class Address {
private:
    std::string street;
    std::string city;
    std::string state;
    std::string zipCode;

public:
    // Constructors, getters, and setters for street, city, state, and zipCode
    bool validateAddress();
    float calculateDistance();
};

#endif

