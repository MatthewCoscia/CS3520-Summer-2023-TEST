
// Program to check if the user-provided number is a palindrome
// Number of errors/bugs = 25


//TODO: Fix the bugs and make sure the program runs as expected.
//Provide a brief comment identifying each bug fixed.


#include<iostream>

// fixes cout issues.
using namespace std;

// rewritten func.
bool func(int n) {
    int original_number = n;
    int reversed_number = 0, remainder;
    while (n != 0) {
        remainder = n % 10;
        reversed_number = reversed_number * 10 + remainder;
        n /= 10;
    }
    if (original_number == reversed_number) {
        return true;
    }
    else {
        return false;
    }
}
// made main an int.
int main() {
    //changed input to int
    int input = 1001;
    cout << "enter an integer please" << "\n";
    cin >> input;
    bool returned_val = func(input);
    if (returned_val) {
        cout << "It is a palindrome";
    }
    else {
        cout << "It is not a palindrome" << endl;
    }
    cout << "\n";

    return 0;
}

