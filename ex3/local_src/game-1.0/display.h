#pragma once
#include <stdint.h>

typedef struct{
	int16_t blue    : 5;
    int16_t green   : 6;
    int16_t red     : 5;
}colour;

typedef struct{
    int width;
    int height;
}fb_info;

/*
    Opens fb driver
    gets info from the driver
    maps the memory
*/
fb_info display_init(void);

/*
    Displays a rectangle. Doh...
    If one or more pixels will be out of bounds,
    none of the pixels will be written.
*/
void display_rectangle(colour set_colour, int x, int y, int width, int height);

/*
    Prints various information about the display.
    Used for debugging.
*/
void display_print_info(void);

/*
    returns:
        1 if the rectangle given has the colour given.
        -1 if one or more pixels do not have the given colour
*/
int display_check_colour_rect(colour set_colour, int x, int y, int width, int height);
