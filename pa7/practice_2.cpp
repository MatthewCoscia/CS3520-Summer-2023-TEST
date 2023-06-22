// Program to read integers into a 3X3 matrix and display them
// Todo: Fix bugs and makesure program works as intended.
// for each bug fix, add a comments specifying what you fixed.

// Number of errors/bugs = 10

#include <iostream>

using namespace std;

void display(int Matrix[3][3], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << Matrix[i][j] << ", ";
        }
        cout << endl;
    }
}

int main(void) {
    const int size = 3;
    // fixed size
    int Matrix[size][size];
    cout << "Enter 9 elements of the matrix:" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cin >> Matrix[i][j];
        }
    }
    display(Matrix, size);
    return 0;
}
