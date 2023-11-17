#include <stdlib.h>
#include  <stdio.h>
#include <time.h>
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

Map initialize_map(int width, int height){
    Map map;
    map.height = height;
    map.width = width;
    map.roboter = (Position){1,1};
    map.staub_count = 0;
    map.turn_count = 0;
    //Speicher allozieren
    map.map = malloc(height*sizeof(char*));
    for(int i = 0; i < height; i++){
        map.map[i] = malloc(width*sizeof(char));
    }
    //Randbefüllen
    for(int i = 0; i < height; i++){
        if(i == 0 || i == height-1){
            for(int j=1; j < width-1; j++) map.map[i][j] = '#';
        }
        map.map[i][0] = '#';
        map.map[i][width-1] = '#';
    }
    //Leerstellen einfügen
    for(int i = 1; i < height-1; i++){
        for(int j = 1; j < width-1; j++){
            map.map[i][j] = ' ';
        }
    }
    //Roboter setzen
    map.map[1][1] = 'S';
    return map;
}

void print_map(Map *map){
    //printf("height:%d width:%d\n", map->height, map->width);
    for(int i = 0; i < map->height; i++){
        printf("\n");
        for(int j = 0; j < map->width; j++){
            printf("%c", map->map[i][j]);
        }
    }
}
void hindernisseverteilen(Map *map, int probability){
    //alte Hindernisse entfernen
    for(int i = 1; i < map->height-1; i++){

        for(int j = 1; j < map->width-1; j++){
            if(map->map[i][j]== '#'){
                    map->map[i][j] = ' ';
                }
        }  
    }
    srand(time(NULL));
    for(int i = 1; i < map->height-1; i++){

        for(int j = 1; j < map->width-1; j++){
            if(map->map[i][j]!= 'S'){
                //Generate Random Integer, equally distributed between 0-99
                int random = 0;
                int Schwellenwert = RAND_MAX - RAND_MAX%100;
                while((random = rand())>Schwellenwert);
                //Check if random integer is lower than probabilty p
                if(random%100 < probability){
                    if(map->map[i][j]=='*') map->staub_count--;
                    map->map[i][j] = '#';
                }
            }
        }
    }
    

}
void staubverteilen(Map *map, int frequency){
    srand(time(NULL));
    for(int i = 1; i < map->height-1; i++){

        for(int j = 1; j < map->width-1; j++){
            if(map->map[i][j]==' '){
                //Generate Random Integer, equally distributed between 0-99
                int random = 0;
                int Schwellenwert = RAND_MAX - RAND_MAX%100;
                while((random = rand())>Schwellenwert);
                //Check if random integer is lower than probabilty p
                if(random%100 < frequency){
                    map->map[i][j] = '*';
                    map->staub_count++;
                }
            }
        }
    }
}
int anfangsstaub(Map *map){
    int count = 0;
    int j = 2;
    for(int i = 1; i < map->height-1; i++){
        if(j = map->width-2){
            j = 2;
        } else {
            j = 1;
        }
        for(; j < map->width-1; j = j+2){
            map->map[i][j] = '*';
            count++;
        }
    }
    map->staub_count = count;
    return count;
}