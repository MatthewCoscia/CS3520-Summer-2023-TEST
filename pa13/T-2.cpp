#include <iostream>
#include <string>
using namespace std;

template <class T>
void findBiggest(T a, T b) // Fixed: Removed the unnecessary second parameter 'int b'
{
    T large = a;
    if (b > large)
        large = b;
    cout << "The larger of " << a << " and " << b << " is " << large << endl; // Fixed: Corrected the variable name 'larger' to 'large'
}

template <class T>
void findBiggest(T a, T b, T c)
{
    T large = a;
    if (b > large)
        large = b;
    if (c > large) // Fixed: Changed the comparison from '<' to '>'
        large = c;
    cout << "The largest of " << a << ", " << b << ", and " << c << " is " << large << endl;
}

class BankAccount
{
    friend ostream &operator<<(ostream &, const BankAccount &);

private:
    string name;
    int amount;

public:
    BankAccount(const string &, int); // Fixed: Added string parameter to match the constructor definition
    bool operator>(const BankAccount &) const; // Fixed: Added const qualifier for the operator function
};

BankAccount::BankAccount(const string &name, int amount) // Fixed: Removed 'const' from the constructor definition
{
    this->name = name; // Fixed: Added 'this->' to distinguish between member variable and parameter
    this->amount = amount; // Fixed: Added 'this->' to distinguish between member variable and parameter
}

ostream &operator<<(ostream &out, const BankAccount &bh)
{
    out << "Name: " << bh.name << ", Amount: " << bh.amount << endl; // Fixed: Corrected the output format and added 'bh.' before member variables
    return out;
}

bool BankAccount::operator>(const BankAccount &bh) const // Fixed: Added const qualifier for the operator function
{
    return amount > bh.amount;
}

int main()
{
    BankAccount bAA("A", 800);
    BankAccount bAB("B", 120);
    BankAccount bAC("C", 500);
    findBiggest(bAA, bAB);
    findBiggest(bAB, bAC);
    findBiggest(bAC, bAA);
    findBiggest(bAA, bAB, bAC);
    return 0;
}
