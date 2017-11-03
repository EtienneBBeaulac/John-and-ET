#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// speak
#define FIFO_NAME "spy_mission"

int main(void)
{
   char message[256];
   char filename[256] = "classified.txt";
   int num, fd;

   mknod(FIFO_NAME, S_IFIFO | 0666, 0);

   printf("Waiting for response from the CIA...\n");
   fd = open(FIFO_NAME, O_WRONLY);
   printf("Connection established.\n");

   while (gets(message), !feof(stdin)) {
      if ((num = write(fd, message, strlen(message))) == -1)
         perror("write");
      else
         printf("Spy stole");
   }

   return 0;
}
