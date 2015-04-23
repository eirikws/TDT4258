#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "display.h"
#include "snake.h"

int main(int argc, char *argv[])
{
    printf("Player %d won!!!\n",snake_game(80));
	exit(EXIT_SUCCESS);
}


