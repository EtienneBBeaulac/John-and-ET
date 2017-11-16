#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

// speak
#define FIFO_NAME "spy_mission"

char contents[2000];
char filename[256];
void type(char message[]);

int readFile()
{
   int c;
   FILE *file;
   file = fopen(filename, "r");
   if (file) {
      int i = 0;
      while ((c = getc(file)) != EOF)
      {
         contents[i] = c;
         i++;
      }
      fclose(file);
      return 1;
   }
   else
      return 0;
}

void receive(int fd)
{
   int num;
   if ((num = read(fd, filename, 256)) == -1)
      perror("read");
   else {
      filename[num] = '\0';
      type("\nReceived oder to steal: ");
      type(filename);
      sleep(1);
      type("\nMission in progress");
      sleep(4);
   }
}

void steal(int fd, int success)
{
   if (success)
   {
      if (write(fd, contents, strlen(contents)) == -1)
         perror("write");
      else
         type("\nSuccessfully sent stolen file to CIA\n");
      sleep(1);
   }
   else
   {
      char fail[256] = "Unable to obtain file";
      if (write(fd, fail, strlen(fail) + 1) == -1)
         perror("write");
      else
         type("\nSent mission report to CIA\n");
      sleep(1);
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
   type("\nWaiting for response from the CIA...");
   // fd = open(FIFO_NAME, O_WRONLY);
   fd = open(FIFO_NAME, O_RDWR);
   sleep(2);
   type("\nConnection established.");
   sleep(1);
   type("\n\nAwaiting orders...");
   
   do {
      receive(fd);
      steal(fd, readFile());
      type("\nAwaiting further instructions\n");
      if ((num = read(fd, message, 256)) == -1)
         perror("read");
      close(fd);
      fd = open(FIFO_NAME, O_RDWR);
   } while (0 != strncmp(message, "2", 1));
   
   sleep(1);
   
   type("\nEnding transmission...");
   sleep(2);
   type("\nGood bye.\n");
   printf("\033[0m");
   // do {
   //    printf("What would you like to do?\n1. Receive an order\n2. Steal documents\n3. End Transmission\n\n");
   //    int result = scanf("%d", &prompt);
   //    if (result == 0) {
   //       while (fgetc(stdin) != '\n') // Read until a newline is found
   //      ;
   //    }
   //    if (prompt == 1)
   //       receive(fd);
   //    else if (prompt == 2)
   //       steal(fd);
   //    else if (prompt == 3)
   //       prompt = 0;
   //    else
   //       printf("Wrong entry.");
   // } while (prompt);
   
   // readFile(filename);
   
   // while (gets(message), !feof(stdin)) {
   //    if (!strncmp(message, "send", 4))
   //       if ((num = write(fd, contents, strlen(contents))) == -1)
   //          perror("write");
   //       else
   //          printf("Spy stole document %s and delivered it to the CIA\n", filename);
   //    else
   //       printf("Wrong input\n");
   // }
   
   return 0;
}

