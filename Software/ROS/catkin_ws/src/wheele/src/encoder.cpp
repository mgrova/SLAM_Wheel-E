#include <iostream>
#include <pigpio.h>

#include <encoder.hpp>

#define SEP_MUESCAS 7.5 //Separacion en grados de las muescas del encoder
#define pi 3.14159265358979
#define n_ticksEnc 22
#define timeout_encoder 500


void re_decoder::_turnOffVel(){

   vel=0.0;
   gpioSetTimerFuncEx(enc_timer_ID,timeout_encoder,NULL,this);

   return;
}
void re_decoder::_pulse(int gpio, int level, uint32_t tick)
{
    
   double tmpVel;

   gpioSetTimerFuncEx(enc_timer_ID,timeout_encoder,NULL,this);

   lev = level;
   if(lastlev>0){
      
      delta_t=(double)gpioTick()/1000-last_t;
      
      tmpVel=((double)(SEP_MUESCAS)/(double)delta_t)*1000; //ticks /s
      tmpVel=tmpVel*(2*pi)/n_ticksEnc;	// rad/s

      if(delta_t==0.0) tmpVel=0.0;

      }
   lastlev=lev;
   last_t=gpioTick()/1000;

   vel=tmpVel;
   gpioSetTimerFuncEx(enc_timer_ID,timeout_encoder,_zeroVel,this);

   return;

}

void re_decoder::_pulseEx(int gpio, int level, uint32_t tick, void *user)
{
   re_decoder *mySelf = (re_decoder *) user;

   mySelf->_pulse(gpio, level, tick);
}
void re_decoder::_zeroVel(void *userdata){

   re_decoder *self = (re_decoder *) userdata;
   self->_turnOffVel();
}

re_decoder::re_decoder(int gpio)
{
   mygpio = gpio;


   lev=0;lastlev=-1;
   delta_t=0;last_t=0;vel=.0;

   enc_timer_ID=no_encoders;
   no_encoders++;

   gpioSetMode(mygpio, PI_INPUT);

   gpioSetPullUpDown(mygpio, PI_PUD_UP);

   gpioSetTimerFuncEx(enc_timer_ID,timeout_encoder,_zeroVel,this);
   
   gpioSetAlertFuncEx(mygpio, _pulseEx, this);

}

void re_decoder::re_cancel(void)
{
   gpioSetAlertFuncEx(mygpio, 0, this);
}

double re_decoder::getVel(void){return vel;}
