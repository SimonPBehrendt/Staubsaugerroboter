#ifndef ROBOTER_H
#define ROBOTER_H
#include <stdbool.h>
typedef enum direction {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    PASS
}direction;
bool is_correct_turn(Map *map, direction direction);
int turn(Map *map, direction d);
direction next_move(char mode);
#endif