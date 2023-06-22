/*game.cpp -------
*
* Filename: game.cpp
* Description:
* Author: Adeel Bhutta
* Maintainer:
* Created: Sat Sep 12 13:16:12 2022
* Last-Updated: September 12 16:51 2022
*
*/

/* Commentary:
*
*
*
*/

/* Change log:
*
*
*/

/*Copyright (c) 2022 Adeel Bhutta
*
* All rights reserved.
*
* Additional copyrights may follow
*/
#include <ncurses.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "snake.hpp"
#include "food.hpp"
#include "game_window.hpp"
#include "key.hpp"
#include "game.hpp"
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>

using namespace std;


void generate_points(int *food_x, int *food_y, int width, int height, int x_offset, int y_offset) {
    *food_x = rand() % width + x_offset;
    *food_y = rand() % height + y_offset;
}

void game() {
    enum State state = STARTMENU; // Set the initial state
    static int x_max, y_max; //Max screen size variables
    static int x_offset, y_offset; // distance between the top left corner of your screen and the start of the board
    gamewindow_t *window; // Name of the board
    Snake *snake; // The snake
    Food *foods, *new_food; // List of foods (Not an array)
    bool difficultySelected = false;

    const int height = 40;
    const int width = 70;
    char ch;
    int charType = 1;
    int lives = 3;
    int speed = 1;
    int obstacle_amount;
    srand(time(NULL));

    struct timespec timeret;
    timeret.tv_sec = 0;
    timeret.tv_nsec = 999999999 / 4;
    state = STARTMENU;
    while (state != EXIT) {
        switch (state) {
            case STARTMENU:
                initscr();
                start_color();
                nodelay(stdscr, TRUE); //Dont wait for char
                noecho(); // Don't echo input chars
                getmaxyx(stdscr, y_max, x_max);
                keypad(stdscr, TRUE); // making keys work
                curs_set(1); // hide cursor
                timeout(100);

                // Setting height and width of the board
                x_offset = (x_max / 2) - (width / 2);
                y_offset = (y_max / 2) - (height / 2);

                //Init board
                window = init_GameWindow(x_offset, y_offset, width, height);
                draw_Gamewindow(window);

                mvprintw(y_offset + (height / 2) - 10, x_offset + (width / 2) - 6, "CHOOSE DIFFICULTY");
                mvprintw(y_offset + (height / 2) - 7, x_offset + (width / 2), "EASY");
                mvprintw(y_offset + (height / 2) - 4, x_offset + (width / 2) - 1, "MEDIUM");
                mvprintw(y_offset + (height / 2) - 1, x_offset + (width / 2), "HARD");
                mvprintw(y_offset + (height / 2) + 10, x_offset + (width / 2) - 10, "Use the arrow keys to move.");
                mvprintw(y_offset + (height / 2) + 13, x_offset + (width / 2) - 10, "To choose difficulty, press E, M, or H");
                char ch;
                while (!difficultySelected) {
                    ch = get_char();
                    if (ch == 'e') {
                        obstacle_amount = 7;
                        difficultySelected = true;
                    }
                    if (ch == 'm') {
                        obstacle_amount = 11;
                        difficultySelected = true;
                    }
                    if (ch == 'h') {
                        obstacle_amount = 15;
                        difficultySelected = true;
                    }
                }
                state = INIT;
                break;
            case INIT:
                initscr();
                start_color();
                nodelay(stdscr, TRUE); //Dont wait for char
                noecho(); // Don't echo input chars
                getmaxyx(stdscr, y_max, x_max);
                keypad(stdscr, TRUE); // making keys work
                curs_set(0); // hide cursor
                timeout(100);

                // Setting height and width of the board
                x_offset = (x_max / 2) - (width / 2);
                y_offset = (y_max / 2) - (height / 2);

                //Init board
                window = init_GameWindow(x_offset, y_offset, width, height);
                draw_Gamewindow(window);

                // Init snake
                snake = init_snake(x_offset + (width / 2), y_offset + (height / 2));
                // Init foods
                int food_x, food_y, i;
                enum Type type;

                //Generate 20 foods
                generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                type = (rand() > RAND_MAX / 2) ? Increase : Decrease; // Randomly deciding type of food
                foods = create_food(food_x, food_y, type, charType);
                charType += 1;
                for (i = 1; i < 12; i++) {
                    generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                    while (food_exists(foods, food_x, food_y) || food_x < x_offset + 1 || food_y < y_offset + 1
                    || food_x > x_offset + width - 1 || food_y > y_offset + height - 1) {
                        generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                    }
                    type = (rand() > RAND_MAX / 2) ? Increase : Decrease;
                    new_food = create_food(food_x, food_y, type, charType);
                    add_new_food(foods, new_food);
                    charType += 1;
                }
                for (int i = 0; i < obstacle_amount; i++) {
                    generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                    while (food_exists(foods, food_x, food_y)) {
                        generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                    }
                    int tempx = food_x;
                    int tempy = food_y;
                    std::vector<int> randomVector = {1, 2};
                    new_food = create_food(tempx, tempy, Obstacle, 0);
                    add_new_food(foods, new_food);
                    int counter = 0;
                    for (int k = 0; k < 10; k++) {
                        if (counter % 3) {
                            auto rng = std::default_random_engine {};
                            std::shuffle(std::begin(randomVector), std::end(randomVector), rng);
                        }
                        int random = randomVector[0];
                        if (random == 1) {
                            tempx += 1;
                        }
                        if (random == 2) {
                            tempy += 1;
                        }
                        if (food_exists(foods, tempx, tempy) || tempx < x_offset + 1 || tempy < y_offset + 1
                                                               || tempx > x_offset + width - 1
                                                               || tempy > y_offset + height - 1
                                                               || (tempx == snake->x && tempy == snake->y)) {
                            break;
                        }
                        else {
                            new_food = create_food(tempx, tempy, Obstacle, 0);
                            add_new_food(foods, new_food);
                            counter += 1;
                        }
                    }
                }


                state = ALIVE;
                break;

            case ALIVE:
                ch = get_char();
                if (ch == 'q') {
                    state = DEAD;
                    clear();
                    break;
                }

                /* Write your code here */
                // Draw everything on the screen
                clear();
                start_color();
                init_pair(1, COLOR_GREEN, COLOR_BLUE);
                attron(COLOR_PAIR(1));
                mvprintw(y_offset - 4, x_offset + 5, "Key entered: %c", ch);
                mvprintw(y_offset - 2, x_offset + 5, "Lives: %i", lives);
                mvprintw(y_offset - 2, x_offset + 15, "Score: %i", snake->score);
                attroff(COLOR_PAIR(1));
                move_snake(snake, ch, speed);
                move_snake_tail(snake->next, speed);
                if (food_exists(foods, snake->x, snake->y)) {
                    eat_food(snake, food_type(foods, snake->x, snake->y));
                    remove_eaten_food(foods, snake->x, snake->y);
                    generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                    while (food_exists(foods, food_x, food_y) || food_x < x_offset + 1 || food_y < y_offset + 1
                           || food_x > x_offset + width - 1 || food_y > y_offset + height - 1) {
                        generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                    }
                    type = (rand() > RAND_MAX / 2) ? Increase : Decrease;
                    new_food = create_food(food_x, food_y, type, charType);
                    charType += 1;
                }
                draw_Gamewindow(window);
                draw_snake(snake);
                draw_food(foods);
                check_if_dead(snake, x_offset, y_offset, height, width);
                if (food_exists(foods, snake->x, snake->y)) {
                    if (food_type(foods, snake->x, snake->y) == '*') {
                        snake->dead = true;
                    }
                }

                if (snake->dead) {
                    lives -= 1;
                    if (lives == 0) {
                        state = DEAD;
                    }
                    else {
                        snake->dead = false;
                    }
                }
                break;

            case DEAD:
                clear();
                initscr();
                start_color();
                std::fstream file;
                file.open("scores.txt", ios::out);
                if (file.is_open()) {
                    file << "\n";
                    file << snake->score;
                }
                file.close();
                nodelay(stdscr, TRUE); //Dont wait for char
                noecho(); // Don't echo input chars
                getmaxyx(stdscr, y_max, x_max);
                keypad(stdscr, TRUE); // making keys work
                curs_set(1); // hide cursor
                timeout(100);

                // Setting height and width of the board
                x_offset = (x_max / 2) - (width / 2);
                y_offset = (y_max / 2) - (height / 2);

                //Init board
                window = init_GameWindow(x_offset, y_offset, width, height);
                draw_Gamewindow(window);
                mvprintw(y_offset + (height / 2), x_offset + (width / 2) - 4, "GAME OVER!");
                endwin();
                break;
        }
        refresh();
        nanosleep(&timeret, NULL);
    }
}
