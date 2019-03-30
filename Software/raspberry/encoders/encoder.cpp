#include <iostream>

#include <pigpio.h>

#include "encoder.hpp"

/*

             +---------+         +---------+      0
             |         |         |         |
   A         |         |         |         |
             |         |         |         |
   +---------+         +---------+         +----- 1

       +---------+         +---------+            0
       |         |         |         |
   B   |         |         |         |
       |         |         |         |
   ----+         +---------+         +---------+  1

*/

void re_decoder::_pulse(int gpio, int level, uint32_t tick)
{
    /*TODO: calcular delta_t*/
   lev = level;
   (mycallback)(1);
   /*Traza*/
   std::cout << "callback llamado" << '\n';
   return;

}

void re_decoder::_pulseEx(int gpio, int level, uint32_t tick, void *user)
{
   /*
      Need a static callback to link with C.
   */

   re_decoder *mySelf = (re_decoder *) user;

   mySelf->_pulse(gpio, level, tick); /* Call the instance callback. */
}

re_decoder::re_decoder(int gpio, re_decoderCB_t callback)
{
   mygpio = gpio;
   mycallback = callback;
   lev=0;

   lastlev=-1;

   gpioSetMode(mygpio, PI_INPUT);

   /* pull up is needed as encoder common is grounded */

   gpioSetPullUpDown(mygpio, PI_PUD_UP);

   /* monitor encoder level changes */

   gpioSetAlertFuncEx(mygpio, _pulseEx, this);

}

void re_decoder::re_cancel(void)
{
   gpioSetAlertFuncEx(mygpio, 0, this);
}
