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

#define WAIT_TIME   1000000000
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
void snake_init_screen( colour edgecolour,colour background,fb_info my_fb_info);
int snake_move(snake *player, colour background);
void snake_cleanup(snake winner, fb_info my_fb_info);
void snake_display_players(snake pl1, snake pl2);
void snake_display_start_screen(snake pl1, snake pl2, fb_info my_fb_info);

void gpio_handler(int signum){
    // find newly pressed button:
    // first find the button that has changed
    // then find if it was pressed (if it was just released we don't care)
    static int last_input;
    int input = 0;
    int pressed;
    
    read( descr, &input, 1);
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

int snake_game(int pix_per_sec){
    srand(time(NULL));
    
    
    fb_info my_fb_info = display_init();
    
    
    colour edgecolour = (colour){   // gold!!
                            .red    = 31,
                            .blue   = 0,
                            .green  = 26};
                            
    colour background = (colour){   // ..magenta?  Might just be pink.
                            .red    = 31,
                            .blue   = 24,
                            .green  = 14};
                            
    snake_init_player(  &player_one,
                        (colour){   .red = 0,   .blue = 0,  .green = 31},
                        my_fb_info );
                        
    snake_init_player(  &player_two,
                        (colour){   .red = 0,   .blue = 31, .green = 0},
                        my_fb_info );
    
    
    struct timespec sleeptime =
                    (struct timespec){  .tv_sec = 2, .tv_nsec = 0};
    // display left half of the screen in player ones colour
    // and right half in player twos colour
    snake_display_start_screen(player_one, player_two, my_fb_info);
    while (nanosleep(&sleeptime, &sleeptime) && errno == EINTR);
    
    // start getting input from the GPIO
    snake_get_gpio(&gpio_handler);
    
    // display the game screen
    snake_init_screen(edgecolour, background,my_fb_info);
    
    
    // display player one
    display_rectangle(  player_one.col,
                        player_one.x,
                        player_one.y,
                        SNAKE_WIDTH,
                        SNAKE_WIDTH);
    // display player two
    display_rectangle(  player_two.col,
                        player_two.x,
                        player_two.y,
                        SNAKE_WIDTH,
                        SNAKE_WIDTH);
    
    sleeptime =(struct timespec){  .tv_sec = 2,
                                   .tv_nsec = 0};
    // wait so that the players can find their snakes and give start input               
    while (nanosleep(&sleeptime, &sleeptime) && errno == EINTR);
    
    while(1) {
        // set the amount of time to sleep
        sleeptime = (struct timespec){  .tv_sec = 0,
                                        .tv_nsec = WAIT_TIME/pix_per_sec};
                                        
        // if the system wakes up from sleep because of interrupts
        // go to sleep again for the remainder of time.
        while (nanosleep(&sleeptime, &sleeptime) && errno == EINTR);
        
        // detect if a snake move is invalid
        // if invalid the other player has won
        if( -1 == snake_move(&player_one, background)){
            snake_cleanup(player_two, my_fb_info);
            return 2;
        }
        if(-1 == snake_move(&player_two, background)){
            snake_cleanup(player_one, my_fb_info);
            return 1;
        }
    }
}

void snake_cleanup(snake winner, fb_info my_fb_info){
    display_rectangle(  winner.col, 0,0,my_fb_info.width,my_fb_info.height);
    close(descr);
    
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
                        fb_info my_fb_info){
                        
   display_rectangle(   background,
                        0,
                        0,
                        my_fb_info.width-1,
                        my_fb_info.height-1);
                        
   display_rectangle(   edgecolour,
                        0,
                        0,
                        my_fb_info.width-1,
                        EDGE_WIDTH);
   
   display_rectangle(   edgecolour,
                        (my_fb_info.width-1)-EDGE_WIDTH,
                        0,
                        EDGE_WIDTH,
                        my_fb_info.height-1);
   
   display_rectangle(   edgecolour,
                        0,
                        (my_fb_info.height-1)-EDGE_WIDTH,
                        my_fb_info.width-1,
                        EDGE_WIDTH);
   
   display_rectangle(   edgecolour,
                        0,
                        0,
                        EDGE_WIDTH,
                        my_fb_info.height-1);
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

void snake_display_start_screen(snake pl1, snake pl2, fb_info my_fb_info){
    display_rectangle(  pl1.col,
                        0,
                        0,
                        my_fb_info.width/2,
                        my_fb_info.height);
    
    display_rectangle(  pl2.col,
                        my_fb_info.width/2,
                        0,
                        my_fb_info.width/2,
                        my_fb_info.height);
}






