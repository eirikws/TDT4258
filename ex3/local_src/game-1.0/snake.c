#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include "display.h"



#define BILLION     1000000000
#define WAIT_TIME   100000000

void time_add(timespec *t1, teimespec *t2){
    t1->tv_sec  = t2->tv_sec + t1->tv_sec;
    t1->tv_nsec = t2->tv_nsec + t1->tv_nsec;
    if (t1->tv_nsec >= BILLION) {
        t1->tv_nsec -=BILLION;
        t1->tv_sec++;
    }
}

typedef enum {WEST, NORTH, EAST, SOUTH} direction;

int map[320][240];

struct player{
    int x;
    int y;
    direction dir;
    colour col;
};

struct player player_one;
struct player player_two;


void snake_init(){
    srand(time(NULL));
             
    player_one = (struct player){  .x = rand() % 320,
                    .y = rand() % 240, 
                    .dir = rand() % 240, 
                    .col = {.red = 10, .blue = 0, .green = 2}};
    player_two = (struct player){  .x = rand() % 320, 
                    .y = rand() % 240, 
                    .dir = rand() % 240,
                    .col = {.red = 2, .blue = 5, .green = 7}};
    
}





void snake() 
{
    snake_init();
    
    display_init();
    
    display_rectangle(player_one.col, player_one.x, player_one.y, 10, 10);
    display_rectangle(player_two.col, player_two.x, player_two.y, 10, 10);
                      
    
    struct timespec sleeptime = { .tv_sec = 0, tv_nsec = WAIT_TIME};
    
    while(1) {
    
    
        while (nanesleep(&sleeptime, &sleeptime) && errno == EINTR);
    
    }
    
    
    // skrive til skjermen
 
    // vente litt
    
    // for each time
    // move x and y for each player based on direction
    // draw a new rectangle
    // store where players have been
    // check if crash
    
    // if interrupt from button
    // change direction
       
   


}












