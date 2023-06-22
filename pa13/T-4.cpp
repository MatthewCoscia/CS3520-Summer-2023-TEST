#include <iostream>
#include <string>
using namespace std;

// Class to perform various operations on two variables of type T
template <class T>
class Calculator
{
private:
    T num1;
    T num2;

public:
    Calculator(T n1, T n2);
    T add();
    T subtract();
    T multiply();
    T divide();
    bool isgreater();
};

template <class T>
Calculator<T>::Calculator(T n1, T n2) // Fixed: Changed the second parameter type to T
{
    num1 = n1;
    num2 = n2;
}

template <class T>
T Calculator<T>::add()
{
    return num1 + num2;
}

template <class T>
T Calculator<T>::subtract()
{
    return num1 - num2;
}

template <class T>
T Calculator<T>::multiply()
{
    return num1 * num2;
}

template <class T>
T Calculator<T>::divide()
{
    return num1 / num2;
}

template <class T>
bool Calculator<T>::isgreater()
{
    return num1 > num2; // Fixed: Removed unnecessary if-else statement
}

int main()
{
    Calculator<int> calc(10, 4); // int operations
    cout << calc.add() << endl;
    cout << calc.subtract() << endl;
    cout << calc.multiply() << endl;
    cout << calc.divide() << endl;
    cout << boolalpha << calc.isgreater() << endl;

    Calculator<double> calc2(10.234, 4.235); // double operations
    cout << calc2.add() << endl;
    cout << calc2.subtract() << endl;
    cout << calc2.multiply() << endl;
    cout << calc2.divide() << endl;
    cout << boolalpha << calc2.isgreater() << endl;

    Calculator<string> calc3("Hello", "World"); // string operations
    cout << calc3.add() << endl;
    cout << boolalpha << calc3.isgreater() << endl;
    return 0;
}
