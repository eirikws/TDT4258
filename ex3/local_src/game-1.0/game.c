#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <linux/fb.h>

int descr;
int buff;
void so_somthing_with_fb(void);


void interrupt_handler(int signum){

    //if(signum ==SIGIO){
    read(   (descr), &buff, 1);
    printf("type: %d    reading %d \n",signum, buff);
    //}
    return;
}

int main(int argc, char *argv[])
{
    //interrupts
    int oflags;
    descr = open("/dev/driver-gamepad", O_RDONLY);
	signal(SIGIO, &interrupt_handler);
	fcntl(  descr, F_SETOWN, getpid());
	oflags = fcntl( descr, F_GETFL);
	fcntl(  descr, F_SETFL, oflags | FASYNC);
	while(1){
        sleep(1);
        printf("mohahahaha\n");
	}

	exit(EXIT_SUCCESS);
}


void so_somthing_with_fb(void){

    int fb_descr, line_size, buffer_size;
	int *screen_memory, *i;
	struct fb_var_screeninfo var_info;
    
    struct fb_fix_screeninfo fixed_info;
    struct fb_var_screeninfo var_info;

    fb_descr = open("/dev/fb0", O_RDWR);
    
    ioctl(fb_descr, FBIOGET_VSCREENINFO, &var_info);
    
    line_size   = var_info.xres * var_info.bits_per_pixel;
    buffer_size = line_size * var_info.yres;
    var_info.xoffset = 0;
    var_info.yoffset = 0;
    ioctl(frambuffer_device, FBIOPAN_DISPLAY, &var_info);
    

}





















