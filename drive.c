/*
 gcc -o drive drive.c -lpigpio -lrt -lpthread

 ./drive [l r lr] [f b]
 ./drive s
*/

#include <stdio.h>
#include <pigpio.h>

#define MOTOR1_FWD 27
#define MOTOR1_BCK 24
#define MOTOR2_FWD 6
#define MOTOR2_BCK 22
#define MOTOR3_FWD 23
#define MOTOR3_BCK 16
#define MOTOR4_FWD 13
#define MOTOR4_BCK 18

#define MOTOR1_EN 5
#define MOTOR2_EN 17
#define MOTOR3_EN 12
#define MOTOR4_EN 25
#define MAX 1
#define MIN 0
#define ON 1
#define OFF 0

int main(int argc, char *argv[])
{
   double start;
   int FWD[4] = {MOTOR1_FWD, MOTOR2_FWD, MOTOR3_FWD, MOTOR4_FWD};
   int BCK[4] = {MOTOR1_BCK, MOTOR2_BCK, MOTOR3_BCK, MOTOR4_BCK};
   int EN[4] = {MOTOR1_EN, MOTOR2_EN, MOTOR3_EN, MOTOR4_EN};
 
   if (gpioInitialise() < 0)
   {
      fprintf(stderr, "pigpio initialisation failed\n");
      return 1;
   }

   /* Set GPIO modes */
   int i = 0;
   for (i = 0; i < 4; i++) {
      gpioSetMode(FWD[i], PI_OUTPUT);
      gpioSetMode(BCK[i], PI_OUTPUT);
      gpioSetMode(EN[i], PI_OUTPUT);

      gpioWrite(FWD[i], MIN);
      gpioWrite(BCK[i], MIN);
      gpioWrite(EN[i], ON);
   }

   if (argc <= 1)
   {
      printf("STOP\n");
   } else {
      int motor1 = MOTOR1_BCK;
      int motor2 = MOTOR4_BCK;
      if (strcmp(argv[2], "f") == 0) {
         printf("FORWARD\n");
         motor1 = MOTOR1_FWD;
         motor2 = MOTOR4_FWD;
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
