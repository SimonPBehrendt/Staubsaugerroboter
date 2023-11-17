#ifndef KARTE_H
#define KARTE_H
typedef struct Position{
    int x;
    int y;
}Position;

typedef struct Map{
    char** map;
    int width;
    int height;
    int staub_count;
    int turn_count;
    Position roboter;
} Map;

Map initialize_map(int width, int height);

void print_map(Map *map);

int anfangsstaub(Map *map);

void hindernisseverteilen(Map *map, int probability);

void staubverteilen(Map *map, int frequency);

#endif