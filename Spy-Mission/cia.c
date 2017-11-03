#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// tick
#define FIFO_NAME "spy_mission"

int main(void)
{
    char message[256];
    int num, fd;

    mknod(FIFO_NAME, S_IFIFO | 0666, 0);

    printf("waiting for spy...\n");
    fd = open(FIFO_NAME, O_RDONLY);
    printf("got a connection with the spy\n");

    do {
        if ((num = read(fd, message, 256)) == -1)
            perror("read");
        else {
            message[num] = '\0';
            printf("CIA: read %d bytes: \"%s\"\n", num, message);
        }
    } while (num > 0);

    return 0;
}
