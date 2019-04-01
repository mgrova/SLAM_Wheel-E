#include <iostream>
#include <unistd.h>
#include <pigpio.h>
#include <stdio.h>
#include "encoder.hpp"


void encoCb(int inc)
{
   static int pos = 0;

   pos += inc;

   std::cout << "pos=" << pos << std::endl;
}

int main(int argc, char **argv)
{
   int GPIO_vect[6];
   re_decoder *encoder;

   if (gpioInitialise() < 0) return 1;

   /*Data type conversion*/
   for (int i=1;i<=argc;i++){
     sscanf(argv[i],"%i",&GPIO_vect[i-1]);
   }

   /*Encoders initialization*/
   for(int i=0;i;i++){
     encoder[i]=re_decoder(GPIO_vect[i],encoCb) ;
   }
   sleep(3000);
   encoder[1].
   // dec.re_cancel();

   gpioTerminate();
}
