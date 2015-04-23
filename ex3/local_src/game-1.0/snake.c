#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "display.h"

#define WAIT_TIME   500000000
#define SNAKE_WIDTH 5
#define EDGE_WIDTH  5


typedef enum {
    WEST    = (1 << 0),
    NORTH   = (1 << 1),
    EAST    = (1 << 2),   
    SOUTH   = (1 << 3),
} direction;


typedef struct{
    int x;
    int y;
    direction dir;
    colour col;
}snake;

/*
    global variables representing the two players' snakes
*/
snake player_one;
snake player_two;
int descr;

void snake_init_player(snake *mysnake, colour snakecolour, fb_info fb_limits);
int snake_get_gpio(void (*func)(int));
void snake_init_screen( colour edgecolour,colour background,fb_info myinfo);
int snake_move(snake *player, colour background);


void gpio_handler(int signum){
    // find newly pressed button:
    // first find the button that has changed
    // then find if it was pressed (if it was just released we don't care)
    static int last_input;
    int input = 0;
    int pressed;
    
    read(   (descr), &input, 1);
    pressed = last_input ^ input;
    pressed = (pressed & input);
    
    if (pressed > 10){
        player_two.dir = (pressed >> 4);
    }
    else if (pressed > 0){
        player_one.dir = pressed;    
    }
    
    last_input = input;
}

int snake_game( int pix_per_sec){
    srand(time(NULL));
    
    
    fb_info myinfo = display_init();
    
    
    colour edgecolour = (colour){   // gold!!
                            .red    = 31,
                            .blue   = 0,
                            .green  = 26};
                            
    colour background = (colour){   // ..magenta?  Might just be pink.
                            .red    = 31,
                            .blue   = 24,
                            .green  = 14};
    
    snake_init_screen(edgecolour, background,myinfo);
    
    
    snake_init_player(  &player_one,
                        (colour){.red = 0  , .blue = 0, .green = 31},
                        myinfo );
                        
    snake_init_player(  &player_two,
                        (colour){.red = 0   , .blue = 31, .green = 0},
                        myinfo );
    
    display_rectangle(  player_one.col,
                        player_one.x,
                        player_one.y,
                        SNAKE_WIDTH,
                        SNAKE_WIDTH);
    
    display_rectangle(  player_two.col,
                        player_two.x,
                        player_two.y,
                        SNAKE_WIDTH,
                        SNAKE_WIDTH);
    
    snake_get_gpio(&gpio_handler);
    
    
    struct timespec sleeptime =
                    (struct timespec){  .tv_sec = 3,
                                        .tv_nsec = 0};
                         
    while (nanosleep(&sleeptime, &sleeptime) && errno == EINTR);
    
    while(1) {
        printf("dir1 %d     dir2: %d \n", player_one.dir,player_two.dir);
        // set the amount of time to sleep
        sleeptime = (struct timespec){  .tv_sec = 0,
                                        .tv_nsec = WAIT_TIME/pix_per_sec};
                                        
        // if the system wakes up from sleep because of interrupts
        // go to sleep again for the remainder of time.
        while (nanosleep(&sleeptime, &sleeptime) && errno == EINTR);
        
        if( -1 == snake_move(&player_one, background)){
            return 2;
        }
        if(-1 == snake_move(&player_two, background)){
            return 1;
        }
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

int snake_move(snake *player, colour background) {
    int can_move;
    switch(player->dir){
        case NORTH:
            can_move = display_check_colour_rect(   background,
                                                    player->x,
                                                    player->y-1,
                                                    SNAKE_WIDTH,
                                                    1);
            if (can_move == -1){
                return -1;
            }
            
            display_rectangle(  player->col,
                                player->x,
                                player->y-1,
                                SNAKE_WIDTH,
                                1);
            player->y--;
            break;
        case EAST:
            can_move = display_check_colour_rect(   background,
                                                    player->x+SNAKE_WIDTH,
                                                    player->y,
                                                    1,
                                                    SNAKE_WIDTH);
            if (can_move == -1){
                return -1;
            }
            
            display_rectangle(  player->col,
                                player->x+SNAKE_WIDTH,
                                player->y,
                                1,
                                SNAKE_WIDTH);
            player->x++;
            break;
        case SOUTH:
            can_move = display_check_colour_rect(   background,
                                                    player->x,
                                                    player->y+SNAKE_WIDTH,
                                                    SNAKE_WIDTH,
                                                    1);
            if (can_move == -1){
                return -1;
            }
            
            display_rectangle(  player->col,
                                player->x,
                                player->y+SNAKE_WIDTH,
                                SNAKE_WIDTH,
                                1);
            player->y++;
            break;
        case WEST:
            can_move = display_check_colour_rect(   background,
                                                    player->x-1,
                                                    player->y,
                                                    1,
                                                    SNAKE_WIDTH);
            if (can_move == -1){
                return -1;
            }
            
            display_rectangle(  player->col,
                                player->x-1,
                                player->y,
                                1,
                                SNAKE_WIDTH);
            player->x--;
            break;
    }
    return 1;
}

void snake_init_screen( colour edgecolour,
                        colour background,
                        fb_info myinfo){
                        
   display_rectangle(   background,
                        0,
                        0,
                        myinfo.width-1,
                        myinfo.height-1);
                        
   display_rectangle(   edgecolour,
                        0,
                        0,
                        myinfo.width-1,
                        EDGE_WIDTH);
   
   display_rectangle(   edgecolour,
                        (myinfo.width-1)-EDGE_WIDTH,
                        0,
                        EDGE_WIDTH,
                        myinfo.height-1);
   
   display_rectangle(   edgecolour,
                        0,
                        (myinfo.height-1)-EDGE_WIDTH,
                        myinfo.width-1,
                        EDGE_WIDTH);
   
   display_rectangle(   edgecolour,
                        0,
                        0,
                        EDGE_WIDTH,
                        myinfo.height-1);
}

int snake_get_gpio(void (*func)(int)){
    int oflags;
    descr = open("/dev/driver-gamepad", O_RDONLY);
    signal(SIGIO, func);
    fcntl( descr, F_SETOWN, getpid());
    oflags = fcntl( descr, F_GETFL);
    fcntl( descr, F_SETFL, oflags | FASYNC);
    return descr;
}

void snake_init_player(snake *mysnake, colour snakecolour, fb_info fb_limit){
    *mysnake = (snake){ .x = EDGE_WIDTH + rand() % fb_limit.width-EDGE_WIDTH*2,
                        .y = EDGE_WIDTH + rand() % fb_limit.height-EDGE_WIDTH*2,
                        .dir = WEST,      // random  dir
                        .col = snakecolour};
}







