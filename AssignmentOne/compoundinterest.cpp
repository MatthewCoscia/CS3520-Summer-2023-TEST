
#include <iostream>

using namespace std;

int main() {
    double principal = 11.0;
    const long max_rand = 1000000L;
    int starting_year = 1626, ending_year = 2023;
    cout << "The starting amount is: " << principal << "\n";
    for (int i = starting_year; i <= ending_year; ++i) {
        double firstdigit = 2 + (rand() % 12);
        double seconddigit = (rand() % 10);
        double thirddigit = (rand() % 10);
        double interest = firstdigit + (seconddigit / 10) + (thirddigit / 100);
        principal = principal + (principal * (interest / 100));
        cout << i << ": " << principal << " at an interest rate of: " << interest << "%" << "\n";
    }
    cout << "The interest results in:" << "\n";
    cout << principal << " dollars." << "\n";
    return 0;
}



