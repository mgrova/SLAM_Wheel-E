#include <iostream>
#include <pigpio.h>

#include <encoder.hpp>

#define SEP_MUESCAS 7.5 //Separacion en grados de las muescas del encoder
#define pi 3.14159265358979
#define n_ticksEnc 22

void re_decoder::_pulse(int gpio, int level, uint32_t tick)
{
    /**/
   double tmpVel;
   gpioSetTimerFuncEx(enc_timer_ID,500,_zeroVel,this);

   lev = level;
   if(lastlev>0){
      /*Solo calcula la "valocidad" en los flancos de bajada*/
      delta_t=(double)gpioTick()/1000-last_t;
      
      tmpVel=(double(SEP_MUESCAS)/(double)delta_t)*1000; //ticks /s
      tmpVel=tmpVel*(2*pi)/n_ticksEnc;	// rad/s

      if(delta_t==0.0) tmpVel=0.0;

      }
   lastlev=lev;
   last_t=gpioTick()/1000;

   vel=tmpVel;
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
void re_decoder::_zeroVel(void *userdata){
   re_decoder *self = (re_decoder *) userdata;
   
   self->vel=0.0;
   gpioSetTimerFuncEx(self->enc_timer_ID,500,NULL,NULL);
}

re_decoder::re_decoder(int gpio)
{
   mygpio = gpio;


   lev=0;lastlev=-1;
   delta_t=0;last_t=0;vel=.0;

   enc_timer_ID=no_encoders;
   no_encoders++;


   gpioSetMode(mygpio, PI_INPUT);

   /* pull up is needed as encoder common is grounded */

   gpioSetPullUpDown(mygpio, PI_PUD_UP);

   /* monitor encoder level changes */
   gpioSetTimerFuncEx(no_encoders,300,_zeroVel,this);
   gpioSetAlertFuncEx(mygpio, _pulseEx, this);

}

void re_decoder::re_cancel(void)
{
   gpioSetAlertFuncEx(mygpio, 0, this);
}

double re_decoder::getVel(void){return vel;}
