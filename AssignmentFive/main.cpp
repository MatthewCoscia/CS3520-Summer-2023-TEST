#include <iostream>
#include <vector>
#include <cstdlib>
#include <thread>
#include <ncurses.h>
#include <ctime>
#include "classes.hpp"
#include "model.hpp"
#include "main.hpp"

using namespace std;

int main() {
    int doodlebug_amount, queen_amount, male_amount, worker_amount, iterations_allowed;
    cout << "Starting Doodlebug Amount: ";
    cin >> doodlebug_amount;
    cout << "Starting Queen Amount: ";
    cin >> queen_amount;
    cout << "Starting Male Ant Amount: ";
    cin >> male_amount;
    cout << "Starting Worker Ant Amount: ";
    cin >> worker_amount;
    cout << "How many iterations before you want the sim to stop?";
    cin >> iterations_allowed;

    // Initialize ncurses
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    generate_array(doodlebug_amount, queen_amount, male_amount, worker_amount);

    for (int y = 0; y < array_height; ++y) {
        for (int x = 0; x < array_width; ++x) {
            // Print the character with square brackets
            main_array[y][x]->setStarve();
            main_array[y][x]->setBreed();
            mvprintw(y, x * 3, "[%c]", main_array[y][x]->getSymbol());
        }
    }

    // Refresh the screen to display the array
    refresh();

    // Wait for user input to exit the program
    int antAmount = 0;
    int doodleBugAmount = 0;
    int iterationCounter = 0;
    bool forceEnded = true;
    while (true) {
        doodleBugAmount = 0;
        antAmount = 0;
        for (int y = 0; y < array_height; ++y) {
            for (int x = 0; x < array_width; ++x) {
                main_array[y][x]->changeMoved(false);
                main_array[y][x]->increaseBreed();
                main_array[y][x]->checkIfFertilized();
            }
        }
        clear();
        for (int y = 0; y < array_height; ++y) {
            for (int x = 0; x < array_width; ++x) {
                main_array[y][x]->eat();
            }
        }
        for (int y = 0; y < array_height; ++y) {
            for (int x = 0; x < array_width; ++x) {
                main_array[y][x]->createOffspring();
            }
        }
        for (int y = 0; y < array_height; ++y) {
            for (int x = 0; x < array_width; ++x) {
                main_array[y][x]->move();
            }
        }
        for (int y = 0; y < array_height; ++y) {
            for (int x = 0; x < array_width; ++x) {
                mvprintw(y, x * 3, "[%c]", main_array[y][x]->getSymbol());
            }
        }
        for (int y = 0; y < array_height; ++y) {
            for (int x = 0; x < array_width; ++x) {
                if (main_array[y][x]->getSymbol() != ' ' && main_array[y][x]->getSymbol() != 'X') {
                    antAmount += 1;
                }
                if (main_array[y][x]->getSymbol() == 'X') {
                    doodleBugAmount += 1;
                }
            }
        }
        iterationCounter += 1;
        if (doodleBugAmount == 0 || antAmount == 0) {
            forceEnded = false;
            break;
        }
        if (iterationCounter == iterations_allowed) {
            forceEnded = true;
            break;
        }
        refresh();
        this_thread::sleep_for(chrono::milliseconds (300));
    }

    // Clean up and exit ncurses
    nocbreak();
    keypad(stdscr, FALSE);
    echo();
    endwin();

    if (forceEnded) {
        cout << "Simulation Finished! This simulation was forcibly finished because the environment was cyclic.";
    } else {
        if (antAmount == 0) {
            cout << "Simulation Finished! The DoodleBugs have Won!";
        }
        if (doodleBugAmount == 0) {
            cout << "Simulation Finished! The Ants have Won!";
        }
    }
    cout << "\n" << "\n";

    return 0;

}

