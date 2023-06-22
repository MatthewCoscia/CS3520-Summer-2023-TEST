/* snake.hpp -------
 *
 * Filename: snake.hpp
 * Description:
 * Author: Adeel Bhutta
 * Maintainer:
 * Created: Sun Sep 13 21:01:02 2022
 * Last-Updated: September 13 22:43 2022
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


struct Snake {
    int x;
    int y;
    int speed;
    char color[3];
    char symbol;
    struct Snake* next;
    struct Snake* prev;
    char movement;
    int score;
    bool dead;
};

typedef struct Snake Snake;

Snake* init_snake(int x, int y);
Snake* create_tail(int x, int y, bool head);
Snake* move_snake(Snake* snake, int direction, int speed);
void move_snake_all(Snake* snake, int speed);
void move_snake_tail(Snake* snake, int speed);
void eat_food(Snake* snake, char type);
void draw_snake(Snake* snake);
void check_if_dead(Snake *snake, int x_offset, int y_offset, int height, int width);
bool eat_itself(Snake* snake);
Snake* remove_tail(Snake* snake);
int len(Snake* snake);
