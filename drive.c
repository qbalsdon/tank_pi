/*
 gcc -o drive drive.c -lpigpio -lrt -lpthread

 ./drive [l r lr] [f b]
 ./drive s
*/

#include <stdio.h>
#include <pigpio.h>

#define MOTOR1_FWD 16
#define MOTOR1_BCK 20
#define MOTOR2_FWD 26
#define MOTOR2_BCK 19
#define MAX 1
#define MIN 0

int main(int argc, char *argv[])
{
   double start;
 
   if (gpioInitialise() < 0)
   {
      fprintf(stderr, "pigpio initialisation failed\n");
      return 1;
   }

   /* Set GPIO modes */
   gpioSetMode(MOTOR1_FWD, PI_OUTPUT);
   gpioSetMode(MOTOR1_BCK, PI_OUTPUT);
   gpioSetMode(MOTOR2_FWD, PI_OUTPUT);
   gpioSetMode(MOTOR2_BCK, PI_OUTPUT);

   gpioWrite(MOTOR1_FWD, MIN);
   gpioWrite(MOTOR1_BCK, MIN);
   gpioWrite(MOTOR2_FWD, MIN);
   gpioWrite(MOTOR2_BCK, MIN);

   if (argc <= 1)
   {
      printf("STOP\n");
   } else {
      int motor1 = MOTOR1_BCK;
      int motor2 = MOTOR2_BCK;
      if (strcmp(argv[2], "f") == 0) {
         printf("FORWARD\n");
         motor1 = MOTOR1_FWD;
         motor2 = MOTOR2_FWD;
      } else {
         printf("BACKWARD\n");
      }
      if (strcmp(argv[1], "l") == 0 || strcmp(argv[1], "lr") == 0) 
      {
         printf("LEFT ON\n");
         gpioWrite(motor1, MAX);
      }
      if (strcmp(argv[1], "r") == 0 || strcmp(argv[1], "lr") == 0)
      {
         printf("RIGHT ON\n");
         gpioWrite(motor2, MAX);
      }
   }
   gpioTerminate();
   return 0;
}
