#include <iostream>
#include <pigpio.h>

#include <encoder.hpp>

#define SEP_MUESCAS 7.5 //Separacion en grados de las muescas del encoder
#define pi 3.14159265358979
#define n_ticksEnc 22

void re_decoder::_pulse(int gpio, int level, uint32_t tick)
{
    /**/
   lev = level;
   if(lastlev>0){
     /*Solo calcula la "valocidad" en los flancos de bajada*/
     delta_t=gpioTick()/1000-last_t;

     vel=(float(SEP_MUESCAS)/(float)delta_t)*1000; //ticks /s
     vel=vel*(2*pi)/n_ticksEnc;	// rad/s

     }
   lastlev=lev;
   last_t=gpioTick()/1000;


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

re_decoder::re_decoder(int gpio)
{
   mygpio = gpio;


   lev=0;lastlev=-1;
   delta_t=0;last_t=0;vel=.0;


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

float re_decoder::getVel(void){return vel;}
