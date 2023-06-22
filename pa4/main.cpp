#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;


// This program will read text from a file
// move it into a 2d vector and a 3d array.
// then print the results.

// vector fullList;
// fstream file;
// for (lines in text) {
//  vector lineList;
//  for (values of text) {
//      lineList.add(value);
//   }
//  for (fullList.length) {
//    file << fullList.get(i)
//    double 3dArray[array_amount][3][2]
//    for (i < array_amount) {
//      for (k < 3) {
//       for (j < 2) {
//         file << 3darray[i][k][j]


int main() {
    fstream numbers;
    numbers.open("numbers.txt", ios::in);
    vector<string> temp_vector;
    if (numbers.is_open()) {
        string tp;
        while(getline(numbers, tp)) {
            temp_vector.push_back(tp);
        }
        numbers.close();
        string t;
        vector<double> perm_vector;
        for (string s : temp_vector) {
            stringstream ss(s);
            while (getline(ss, t, ' ')) {
                double temp;
                try {
                    temp = stod(t);
                }
                catch (exception e) {
                    throw new exception(e);
                }
                perm_vector.push_back(temp);
            }
        }
        fstream resultfile;
        resultfile.open("resultfile.txt", ios::out);
        if (resultfile.is_open()) {
            resultfile << "2D Vector:" << "\n";
            vector<double> temp_double_vector;
            for (double d: perm_vector) {
                temp_double_vector.push_back(d);
                if (temp_double_vector.size() == 4) {
                    for (double d: temp_double_vector) {
                        resultfile << d << " ";
                    }
                    resultfile << "\n";
                    temp_double_vector = {};
                }
            }
            while (perm_vector.size() % 6 != 0) {
                perm_vector.push_back(0.0);
            }
            int array_size = perm_vector.size() / 6;
            double threeDArray[array_size][3][2];
            int counter = 0;
            for (int i = 0; i < array_size; ++i) {
                for (int k = 0; k < 3; ++k) {
                    for (int j = 0; j < 2; ++j) {
                        threeDArray[i][k][j] = perm_vector[counter];
                        counter++;
                    }
                }
            }
            for (int i = 0; i < array_size; ++i) {
                if (i == 0) {
                    resultfile << "3D Array:" << "\n";
                }
                else {
                    resultfile << "\n";
                }
                for (int k = 0; k < 3; ++k) {
                    if (i != 0 || k != 0) {
                        resultfile << "\n";
                    }
                    for (int j = 0; j < 2; ++j) {
                        resultfile << threeDArray[i][k][j] << " ";
                    }
                }
            }
            resultfile.close();
        }
    }
    else {
        cout << "File could not be found";
    }
}
