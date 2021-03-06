#include <stdio.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "display.h"

/*
    Because there is only one screen, a global variable is OK
*/

typedef struct{
    int fb_descr;
    colour *screen_memory;
    struct fb_fix_screeninfo fixed_info;
    struct fb_var_screeninfo var_info;
}display_info;

display_info display;

fb_info display_init(void){
    display.fb_descr = open("/dev/fb0", O_RDWR);
    if (display.fb_descr == -1){
        printf("Error opening frame buffer\n");
    }
    if (ioctl(display.fb_descr, FBIOGET_FSCREENINFO, &display.fixed_info) == -1){
        printf("Error get fixed info\n");
    }
    if (ioctl(display.fb_descr, FBIOGET_VSCREENINFO, &display.var_info) == -1){
        printf("Error get variable info\n");
    }
    
    display.screen_memory =
        (colour*)mmap(  NULL,          // Don't care where in the memory
                        display.fixed_info.smem_len, // Length of memory required
                        PROT_READ | PROT_WRITE, //be able to both read and write
                        MAP_SHARED,
                        display.fb_descr,
                        0);                     // zero offset
                        
    if (display.screen_memory == MAP_FAILED){
        printf("Mapping failed\n");
    }
    return (fb_info){ 
                .width  = display.var_info.xres,
                .height = display.var_info.yres};
}

void display_rectangle(    colour set_colour,
                        int x,
                        int y,
                        int width,
                        int height){
    int i, j;
    struct fb_copyarea rect;
    rect.dx = x;
    rect.dy = y;
    rect.width = width;
    rect.height = height;

    for(i = y; i < (y + height) ; i++){
        for(j = x; j < (x + width); j++){
            display.screen_memory[ j
               +display.fixed_info.line_length/sizeof(colour)*i] = set_colour;
        }       
    }
    ioctl(display.fb_descr, 0x4680, &rect);
}

void display_print_info(void){
    printf("size of colour: %d \n", sizeof(colour));
    printf("size of int16:  %d \n", sizeof(int16_t));
    printf("smem length:    %d \n", display.fixed_info.smem_len);
    printf("line length:    %d \n", display.fixed_info.line_length);
    printf("xres:           %d \n", display.var_info.xres);
    printf("yres:           %d \n", display.var_info.yres);
    printf("xres_virtual:   %d \n", display.var_info.xres_virtual);
    printf("yres_virtual:   %d \n", display.var_info.yres_virtual);
    printf("xoffset:        %d \n", display.var_info.xoffset);
    printf("yoffset:        %d \n", display.var_info.yoffset);
    printf("bits per pixel: %d \n", display.var_info.bits_per_pixel);
    printf("height:         %d \n", display.var_info.height);
    printf("width:          %d \n", display.var_info.width); 
}

int colour_comp(colour co1, colour co2){
    if (co1.red == co2.red && co1.blue == co2.blue && co1.green == co2.green){
        return 1;
    }
    return 0;
}

int display_check_colour_rect(colour check_colour, int x, int y, int width, int height){
    int i,j,comp;
    for(i = y; i < (y + height) ; i++){
        for(j = x; j < (x + width); j++){
            comp = colour_comp( check_colour,
                display.screen_memory[ j+(display.fixed_info.line_length/sizeof(colour))*i]);
            if (!comp){
                return -1;
            }
        }       
    }
    return 1;
}



