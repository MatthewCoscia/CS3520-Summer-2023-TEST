/* snake.cpp -------
 *
 * Filename: snake.cpp
 * Description:
 * Author: Adeel Bhutta
 * Maintainer:
 * Created: Sun Sep 13 9:12:30 2022
 * Last-Updated: September 13 22:40 2022
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

/* Copyright (c) 2022 Adeel Bhutta
 *
 * All rights reserved.
 *
 * Additional copyrights may follow
 */

#include <cstring>
#include <cstdbool>
#include <cstdlib>
#include "snake.hpp"
#include "key.hpp"
#include "food.hpp"
#include <ncurses.h>

// Initialize snake
Snake *init_snake(int x, int y) {
    Snake *head = create_tail(x, y, true);
    Snake *tail1 = create_tail(x - 1, y, false);
    Snake *tail2 = create_tail(x - 2, y, false);
    tail1->next = tail2;
    head->next = tail1;
    tail1->prev = head;
    tail2->prev = tail2;
    head->score = 3;
    head->dead = false;
    return head;
}

// Creates one tail
Snake *create_tail(int x, int y, bool head) {
    Snake *snake = new Snake;
    snake->color[0] = 0;
    snake->color[1] = 0;
    snake->color[2] = 255;
    /* snake->color = {0, 0, 255}; */
    if (head) {
        snake->symbol = 'W';
    } else {
        snake->symbol = '#';
    }
    snake->next = NULL;
    snake->x = x;
    snake->y = y;
    return snake;
}

void eat_food(Snake *snake, char type) {
    if (type == 'O' || type == 'P') {
        snake->score += 1;
    }
    if (type == 'X' || type == 'Z') {
        remove_tail(snake);
        snake->score -= 1;
        return;
    }
    if (snake->next == nullptr) {
        if (type == 'O') {
            if (snake->movement == UP) {
                snake->next = create_tail(snake->x, snake->y - 1, false);
                snake->next->prev = snake;
            }
            if (snake->movement == DOWN) {
                snake->next = create_tail(snake->x, snake->y + 1, false);
                snake->next->prev = snake;
            }
            if (snake->movement == RIGHT) {
                snake->next = create_tail(snake->x + 1, snake->y, false);
                snake->next->prev = snake;
            }
            if (snake->movement == LEFT) {
                snake->next = create_tail(snake->x - 1, snake->y, false);
                snake->next->prev = snake;
            }
        }
        return;
    }
    else {
        eat_food(snake->next, type);
    }
}

// moves the snake's tail.
void move_snake_tail(Snake *snake, int speed) {
    if (snake == nullptr) {
        return;
    }
    switch (snake->prev->movement) {
        case UP:
            if (snake->x != snake->prev->x) {
                if (snake->prev->x > snake->x) {
                    snake->x += 1;
                    snake->movement = RIGHT;
                }
                if (snake->prev->x < snake->x) {
                    snake->x -= 1;
                    snake->movement = LEFT;
                }
            }
            else {
                snake->y = snake->prev->y + 1;
                snake->movement = UP;
            }
            if (snake->next != nullptr) {
                snake->next->prev = snake;
            }
            break;
        case DOWN:
            if (snake->x != snake->prev->x) {
                if (snake->prev->x > snake->x) {
                    snake->x += 1;
                    snake->movement = RIGHT;
                }
                if (snake->prev->x < snake->x) {
                    snake->x -= 1;
                    snake->movement = LEFT;
                }
            }
            else {
                snake->y = snake->prev->y - 1;
                snake->movement = DOWN;
            }
            if (snake->next != nullptr) {
                snake->next->prev = snake;
            }
            break;
        case RIGHT:
            if (snake->y != snake->prev->y) {
                if (snake->prev->y > snake->y) {
                    snake->y += 1;
                    snake->movement = DOWN;
                }
                if (snake->prev->y < snake-> y) {
                    snake-> y -= 1;
                    snake->movement = UP;
                }
            }
            else {
                snake->x = snake->prev->x - 1;
                snake->movement = RIGHT;
            }
            if (snake->next != nullptr) {
                snake->next->prev = snake;
            }
            break;
        case LEFT:
            if (snake->y != snake->prev->y) {
                if (snake->prev->y > snake->y) {
                    snake->y += 1;
                    snake->movement = DOWN;
                }
                if (snake->prev->y < snake-> y) {
                    snake-> y -= 1;
                    snake->movement = UP;
                }
            }
            else {
                snake->x = snake->prev->x + 1;
                snake->movement = LEFT;
            }
            if (snake->next != nullptr) {
                snake->next->prev = snake;
            }
            break;
    }
    move_snake_tail(snake->next, speed);
}

// moves the head of the snake
void move_snake_all(Snake *snake, int speed) {
    switch (snake->movement) {
        case UP:
            snake->y = snake->y - speed * 1;
            snake->movement = UP;
            break;
        case DOWN:
            snake->y = snake->y + speed * 1;
            snake->movement = DOWN;
            break;
        case RIGHT:
            snake-> x = snake->x + speed * 1;
            snake->movement = RIGHT;
            break;
        case LEFT:
            snake-> x = snake->x - speed * 1;
            snake->movement = LEFT;
            break;
    }

}

void check_if_dead(Snake *snake, int x_offset, int y_offset, int height, int width) {
    if (snake->x <= x_offset || snake->x >= x_offset + width
    || snake->y <= y_offset || snake->y >= y_offset + height) {
        snake->dead = true;
    }

}

// Moves the snake in the input direction
Snake *move_snake(Snake *snake, int direction, int speed) {
    // TODO
    Snake *new_head = new Snake;

    // Set the new head to have the x and y coordinates as the existing head of the snake

    switch (direction) {
        case UP:
            snake->movement = UP;
            snake->next->prev = snake;
            move_snake_all(snake, speed);
            break;
        case DOWN:
            snake->movement = DOWN;
            snake->next->prev = snake;
            move_snake_all(snake, speed);
            break;
        case RIGHT:
            snake->movement = RIGHT;
            snake->next->prev = snake;
            move_snake_all(snake, speed);
            break;
        case LEFT:
            snake->movement = LEFT;
            snake->next->prev = snake;
            move_snake_all(snake, speed);
            break;
        default:
            snake->next->prev = snake;
            move_snake_all(snake, speed);
            break;
    }

    // Set new head as the new head of the entire snake
    // Add all the features (color and symbol) to the new cell
    //  Delete the tail from the snake: HINT - there is a remove tail function below

    return new_head;
}

Snake *remove_tail(Snake *snake) {
    Snake *end = snake;
    while (end->next->next)
        end = end->next;
    free(end->next);
    end->next = NULL;
    return snake;
}

// draws the snake on the board
void draw_snake(Snake *snake) {
    while (snake) {
        mvprintw(snake->y, snake->x, "%c", snake->symbol);
        snake = snake->next;
    }
}

// checks if it eats itself, if it does, then return true
bool eat_itself(Snake *snake) {
    return true;
    // TODO for Milestone 2 only
}


