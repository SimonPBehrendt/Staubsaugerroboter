#include <stdlib.h>
#include  <stdio.h>
#include "karte.h"
#include "roboter.h"



int main(int argc, char **argv){
    printf("\nProgrammStart:\n");
    int width = 20;
    int height = 20;
    int staub_count = 0;
    if(argc == 3){
        width = atoi(argv[1]);
        height = atoi(argv[2]);
    }
    //Initilaize Map
    Map map = initialize_map(width, height);
    //print_map(&map);

    //Anfangsstaub
    staub_count = anfangsstaub(&map);
    print_map(&map);

    //Anfangshindernisse
    int obstacle_distrubution = 0;
    printf("\nEnter the Obstacle-distribution 0-100?\n");
    scanf("%i", &obstacle_distrubution);
    hindernisseverteilen(&map, obstacle_distrubution);
    print_map(&map);
    fflush(stdin); 

    //Staubgenerationsvariablen
    int dust_frequency = 0;
    int dust_distrubution = 0;
    printf("\nEnter dust_frequency and dust_distrubution: X Y\n");
    scanf("%i %i", &dust_frequency, &dust_distrubution);
    fflush(stdin); 

    //Hindernesgenerationsvariablen
    int obstacle_frequency = 0;
    printf("\nEnter obstacle_frequency\n");
    scanf("%i", &obstacle_frequency);
    fflush(stdin); 

    //wer spielt?
    char answer; 
    printf("\nWant to play for yourself(y) or let the algorithm do it(n)?\n");
    scanf("%c", &answer);
    //Nutzer spielt
    if(answer == 'y'){
        printf("playing");
    } else {
        //TODO: Algorithmen implementieren
        printf("not implemented yet");
    }

    //Playing the Game
    while(map.staub_count!= 0){
        if(dust_frequency!= 0 && map.turn_count!=0 && map.turn_count%dust_frequency==0){
            staubverteilen(&map, dust_frequency);
        }
        if(obstacle_frequency!= 0 && map.turn_count!=0 && map.turn_count%obstacle_frequency==0){
            hindernisseverteilen(&map, obstacle_distrubution);
        }
        turn(&map, next_move(answer));
        print_map(&map);
    }
    printf("\ngreat success\n");
    return 0;
}