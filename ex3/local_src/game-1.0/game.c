#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <unistd.h>
#include <signal.h>

#include "display.h"

int descr;
int buff;

void interrupt_handler(int signum){

    //if(signum ==SIGIO){
    read(   (descr), &buff, 1);
    printf("type: %d    reading %d \n",signum, buff);
    //}
    return;
}

int main(int argc, char *argv[])
{
    colour mycolour = {.red = 10, .blue = 0, .green = 2};
    display_init();
    display_print_info();
    display_rectangle(mycolour, 20, 10, 290, 20);
    
    
    
    /*
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
	*/

	exit(EXIT_SUCCESS);
}























