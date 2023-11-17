#include <stdlib.h>
#include  <stdio.h>
#include <ctype.h>
#include "karte.h"
#include <stdbool.h>
typedef enum direction {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    PASS
}direction;

//tries to get next turn either by algorithm or user input y = user, n = computer
direction next_move(char mode){
    direction d;
    //USER playing
    if(mode == 'y'){
        char c;
        fflush(stdin); 
        printf("\nNext Move? Type W(UP), A(LEFT), S(DOWN), D(RIGHT)\n");
        scanf("%c", &c);
        c = toupper(c);
        switch(c){
            case 'W':
                d = UP;
                break;
            case 'A':
                d = LEFT;
                break;
            case 'S':
                d = DOWN;
                break;
            case 'D':
                d = RIGHT;
                break;
            default:
                printf("\nWrong input\n");
                d = PASS; 
        }
    //Computer playing
    } else if(mode == 'n'){
        //TODO: Implement
    } else {
        printf("trying: next move, wrong mode input\n");
        return PASS;
    }
    return d;
}
bool is_correct_turn(Map *map, direction direction){
    if(direction == UP && map->map[map->roboter.y-1][map->roboter.x]=='#') return false;
    if(direction == DOWN && map->map[map->roboter.y+1][map->roboter.x]=='#') return false;
    if(direction == LEFT && map->map[map->roboter.y][map->roboter.x-1]=='#') return false;
    if(direction == RIGHT && map->map[map->roboter.y][map->roboter.x+1]=='#') return false;
    return true;
}
int turn(Map *map, direction direction){
    Position new_position = {0,0};
    //printf("POSITION:%d, %d", map->roboter.x, map->roboter.y);
    
    //Bewegung vorbereiten
    if(is_correct_turn(map, direction)){
        switch (direction){
            case UP:
                new_position = (Position){map->roboter.x, map->roboter.y-1};
                break;
            case DOWN:
                new_position = (Position){map->roboter.x, map->roboter.y+1};
                break;
            case LEFT:
                new_position = (Position){map->roboter.x-1, map->roboter.y};
                break;
            case RIGHT:
                new_position = (Position){map->roboter.x+1, map->roboter.y};
                break;
            default:
                new_position = (Position){map->roboter.x, map->roboter.y};
        }
            
    } else {
        return map->staub_count;
    }
    //Staubsaugen
    if(map->map[new_position.y][new_position.x]=='*'){
        map->staub_count--;
    }
    //Bewegung;
    map->map[map->roboter.y][map->roboter.x] = ' ';
    map->map[new_position.y][new_position.x] = 'S';
    map->roboter.x = new_position.x;
    map->roboter.y = new_position.y;
    map->turn_count++;
    return map->staub_count;
}