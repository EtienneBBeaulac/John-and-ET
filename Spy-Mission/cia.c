#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

// tick
#define FIFO_NAME "spy_mission"

void type(char message[]);

void order(int fd)
{
   char order[256];
   type("\nEnter desired document name: ");
   // read_line(order, 256);
   if (fgets(order, sizeof order, stdin)) {
       order[strcspn(order, "\n")] = '\0';
   }
   if (write(fd, order, strlen(order)) == -1)
      perror("write");
   else
      type("\nSent order to spy\n\n");
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
      type("Receiving information...\n\n");
      sleep(2);
      type("Obtained information:\n");
      type("\"");
      type(message);
      type("\"");
   }
}

void type(char message[])
{
   for (int i = 0; i < strlen(message); i++)
   {
   	printf("\033[1;32m");
      printf("%c", message[i]);
      fflush( stdout );
      nanosleep((const struct timespec[]){{0, 20000000L}}, NULL);
   }
}

int main(void)
{
   char message[256];
   int num, fd;

   mknod(FIFO_NAME, S_IFIFO | 0666, 0);

   type("\nWaiting for spy...");
   fd = open(FIFO_NAME, O_RDWR);
   sleep(3);
   type("\nConnection established.\n");
   sleep(1);

   do {
   order(fd);
   receive(fd);
   sleep(2);
   type("\n\nWhat would you like to do next:\n1. Send new order\n2. End transmission\n> ");
   if (fgets(message, sizeof message, stdin)) {
       message[strcspn(message, "\n")] = '\0';
   }
   // read_line(message, 256);
   if (write(fd, message, strlen(message)) == -1)
      perror("write");
   close(fd);
   fd = open(FIFO_NAME, O_RDWR);
   } while (0 != strncmp(message, "2", 1));

   sleep(1);

   type("\nEnding transmission...");
   sleep(2);
   type("\nGood bye.\n");
    printf("\033[0m");

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
