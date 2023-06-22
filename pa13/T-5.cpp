#include <iostream>
#include <string>

using namespace std;

class car {
protected:
    string name;
    int modelYear;

public:
    car(const string& n, const int my) : name(n), modelYear(my) {}

    virtual void print() const {
        cout << "Name: " << name << " Model Year: " << modelYear << endl;
    }

    virtual const car& operator=(const car& c) {
        name = c.name;
        modelYear = c.modelYear;
        return *this;
    }
};

class sedan : public car {
private:
    int mileage;

public:
    sedan(const string& n, const int my, const int m) : car(n, my), mileage(m) {}

    void print() const override {
        cout << "Name: " << name << " Model Year: " << modelYear << " Mileage: " << mileage << endl;
    }
};

class suv : public car {
private:
    int miles;

public:
    suv(const string& n, const int my, const int m) : car(n, my), miles(m) {}

    void print() const override {
        cout << "Name: " << name << " Model Year: " << modelYear << " Miles driven: " << miles << endl;
    }

    const suv& operator=(const car& c) override {
        if (const suv* b = dynamic_cast<const suv*>(&c)) {
            car::operator=(*b); // Invoke the base class operator=
            miles = b->miles; // Access the protected member of the base class
        }
        return *this;
    }
};

void printCarInfo(const car& c) {
    c.print();
}

int main() {
    car tesla("Tesla", 2019);
    sedan hyundai("Hyundai", 2020, 23);
    suv ford("Ford", 2012, 20000);

    printCarInfo(tesla);
    printCarInfo(hyundai);
    printCarInfo(ford);

    suv ford2("Ford", 2017, 10000);
    car& ref = ford2;
    printCarInfo(ref);

    return 0;
}
