#include <iostream>
#include <pigpio.h>

#include <encoder.hpp>
#include <numeric>

void re_decoder::_turnOffVel(){

   vel=0.0;
   gpioSetTimerFuncEx(enc_timer_ID,TIMEOUT_ENCD,NULL,this);

   return;
}
void re_decoder::_pulse(int gpio, int level, uint32_t tick)
{
   double tmpVel;

   gpioSetTimerFuncEx(enc_timer_ID,TIMEOUT_ENCD,NULL,this);

   lev = level;

   if(lastlev>0){

      delta_t=(double)gpioTick()/1000-last_t;

      tmpVel=((double)(SEP_MUESCAS)/(double)delta_t)*1000; //ticks /s
      tmpVel=tmpVel*(2*PI)/360.0;	// rad/s

      if(delta_t==0.0) tmpVel=0.0;

      buffer_vel.pop_back();
      buffer_vel.insert(buffer_vel.begin(),tmpVel);

      }
   lastlev=lev;
   last_t=gpioTick()/1000;

   vel=std::accumulate(buffer_vel.begin(),buffer_vel.end(),0.0)/(double)buffer_vel.size();

   gpioSetTimerFuncEx(enc_timer_ID,TIMEOUT_ENCD,_zeroVel,this);

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
   buffer_vel.resize(WDW);

   lev=0;lastlev=-1;
   delta_t=0;last_t=0;vel=.0;

   enc_timer_ID=no_encoders;
   no_encoders++;

   gpioSetMode(mygpio, PI_INPUT);

   gpioSetPullUpDown(mygpio, PI_PUD_UP);

   gpioSetTimerFuncEx(enc_timer_ID,TIMEOUT_ENCD,_zeroVel,this);

   gpioSetAlertFuncEx(mygpio, _pulseEx, this);

}

void re_decoder::re_cancel(void)
{
   gpioSetAlertFuncEx(mygpio, 0, this);
}

double re_decoder::getVel(void){return vel;}
