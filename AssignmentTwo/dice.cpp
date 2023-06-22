#include <iostream>

using namespace std;

int Dice() {
    int combination_results[7][7];
    int sum_results[11];
    for (int i = 0; i < 7; ++i) {
        for (int k = 0; k < 7; ++k) {
            combination_results[i][k] = 0;
        }
    }
    for (int i = 0; i < 11; ++i) {
        sum_results[i] = 0;
    }
    int dice_results[36000][2];
    for (int i = 0; i < 36000; ++i) {
        dice_results[i][0] = 1 + rand() % 6;
        dice_results[i][1] = 1 + rand() % 6;
    }
    for (int i = 0; i < 36000; ++i) {
        int first_roll = dice_results[i][0];
        int second_roll = dice_results[i][1];
        combination_results[first_roll][second_roll] += 1;
        int sum_pos = first_roll + second_roll - 2;
        sum_results[sum_pos] += 1;
    }
    cout << "Combination Results:" << "\n";
    cout << "   1   2   3   4   5    6" << "\n";
    for (int i = 1; i < 7; ++i) {
        cout << i << " ";
        for (int k = 1; k < 7; ++k) {
            cout << combination_results[i][k] << " ";
        }
        cout << "\n";
    }
    cout << "Sum Results:" << "\n";
    for (int i = 0; i < 11; ++i) {
        cout << i + 2 << ": ";
        cout << sum_results[i] << "\n";
    }
}
