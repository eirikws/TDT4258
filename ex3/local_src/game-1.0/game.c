#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "display.h"
#include "snake.h"

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
    int oflags;
    descr = open("/dev/driver-gamepad", O_RDONLY);
	signal(SIGIO, &interrupt_handler);
	fcntl(  descr, F_SETOWN, getpid());
	oflags = fcntl( descr, F_GETFL);
	fcntl(  descr, F_SETFL, oflags | FASYNC);
    snake();
	exit(EXIT_SUCCESS);
}





















