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

void order(int fd)
{
   char order[256];
   printf("\nEnter desired document name: ");
   gets(order);
   if (write(fd, order, strlen(order)) == -1)
      perror("write");
   else
      printf("\nSent order to spy\n\n");
}

void receive(int fd)
{
   int num;
   char message[2000];
   if ((num = read(fd, message, 256)) == -1)
      perror("read");
   else {
      message[num] = '\0';
      message[num - 1] = '\0';
      printf("Receiving information...\n\n");
      sleep(2);
      printf("Obtained information: \n\"%s\"\n\n", message);
   }
}

int main(void)
{
   char message[256];
   int num, fd;

   mknod(FIFO_NAME, S_IFIFO | 0666, 0);

   printf("\nWaiting for spy...\n");
   fd = open(FIFO_NAME, O_RDWR);
   printf("Connection established.\n");

   do {
   order(fd);
   receive(fd);
   printf("\nWhat would you like to do next:\n1. Send new order\n2. End transmission\n> ");
   gets(message);
   if (write(fd, message, strlen(message)) == -1)
      perror("write");
   close(fd);
   fd = open(FIFO_NAME, O_RDWR);
   } while (0 != strncmp(message, "2", 1));

   sleep(1);

   printf("Ending transmission...\n");
   sleep(2);
   printf("Good bye.\n");

   // char prompt[1];
   // do {
   //    printf("What would you like to do?\n1. Send an order\n2. Retrieve information\n3. End Transmission\n\n");
   //    gets(prompt);
   //
   //    if (0 == strncmp(prompt, "1", 1))
   //       order(fd);
   //    else if (0 == strncmp(prompt, "2", 1))
   //       receive(fd);
   //    else
   //       printf("Wrong entry.");
   // } while (0 != strncmp(prompt, "3", 1));

   return 0;
}
