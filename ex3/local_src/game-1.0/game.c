#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

int descr;
int buff;

__signal_handler_t interrupt_handler(void){
    read(descr, &buff, 1);
    printf("reading %d \n", buff);
    return;
}

int main(int argc, char *argv[])
{
    int oflags;
    descr = open("/dev/gamepad-driver", O_RDONLY);
	signal(SIGIO, &interrupt_handler);
	fcntl(STDIN_FILENO, F_SETOWN, getpid());
	oflags = fcntl(STDIN_FILENO, F_GETFL);
	fcntl(STDIN_FILENO, F_SETFL, oflags | FASYNC);
	while(1){
        sleep(1);
        printf("mohahahaha\n");
	}
	exit(EXIT_SUCCESS);
}
