#include <iostream>

using namespace std;

class forAssignment {
 public:
    int non_static_public_var;
    static int static_public_var;
    void setVariables();
    void print() {
        cout <<
        "non_static_private_var: " << &non_static_private_var << "\n" <<
        "static_public_var: " << &static_public_var << "\n" <<
        "non_static_private_var: " << &non_static_private_var << "\n" <<
        "static_private_var: " << &static_private_var;
    }
private:
    string non_static_private_var;
    static string static_private_var;
};

int forAssignment::static_public_var = 1;
string forAssignment::static_private_var = "This is a static private variable";

void forAssignment::setVariables() {
    non_static_public_var = 1;
    non_static_private_var = "Hello";
}

// my comments on what I have observed:
// the static variables have the same memory addresses, while
// the non static variables have different memory addresses.
// I think that this is due to the fact that a static variable
// takes up the same amount of memory space no matter what.
// So, even though we are initializing two different variables,
// because they are of the same class, the static variables have the same
// memory values.
int main() {
    forAssignment testVariable1;
    forAssignment testVariable2;
    cout << "testVariable1: " << &testVariable1<< "\n" <<
    "testVariable2: " << &testVariable2 << endl;
    testVariable1.setVariables();
    testVariable2.setVariables();
    cout << "testVariable1:" << "\n";
    testVariable1.print();
    cout << "\n";
    cout << "testVariable2:" << "\n";
    testVariable2.print();
    return 0;
}