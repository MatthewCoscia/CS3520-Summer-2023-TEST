#include <iostream>
#include <string>
using namespace std;

template <class T>
T add(T x, T y) // Fixed: Added missing type specifier for the second parameter
{
    T sum; // Fixed: Corrected the variable type to match the template type
    sum = x + y;
    return sum;
}

class Person
{
    friend ostream &operator<<(ostream &, const Person &);

private:
    string lastName;
    string firstName;
    int age;

public:
    void setValues(string, string, int);
    Person operator+(const Person&); // Fixed: Added const qualifier for the parameter
};

ostream &operator<<(ostream &out, const Person &per) // Fixed: Added const qualifier for the parameter
{
    out << per.firstName << " " << per.lastName << ", " << per.age << " years old" << endl; // Fixed: Added missing comma and fixed the output format
    return out;
}

void Person::setValues(string last, string first, int personAge) // Fixed: Changed the parameter name to avoid conflict with the member variable
{
    lastName = last;
    firstName = first;
    age = personAge; // Fixed: Assign the parameter to the member variable
}

Person Person::operator+(const Person &p) // Fixed: Added const qualifier for the parameter
{
    Person temp;
    temp.lastName = lastName + " " + p.lastName; // Fixed: Concatenated last names with a space in between
    temp.firstName = firstName + " " + p.firstName; // Fixed: Concatenated first names with a space in between
    temp.age = age + p.age; // Fixed: Corrected the logic to add the ages
    return temp;
}

int main()
{
    int a = 7, b = 26, c;
    double d = 39.25, e = 2.01, f;
    Person g, h, i;
    g.setValues("Mitchell", "Donald", 40);
    h.setValues("Clayton", "Rita", 35);
    c = add(a, b);
    f = add(d, e);
    i = add(g, h);
    cout << c << endl;
    cout << f << endl;
    cout << i << endl;
    return 0;
}
