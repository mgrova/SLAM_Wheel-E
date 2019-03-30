#ifndef ROTARY_ENCODER_HPP
#define ROTARY_ENCODER_HPP

#include <stdint.h>

typedef void (*re_decoderCB_t)(int);

class re_decoder
{
   int mygpio, lev, lastlev, delta_t, last_t;
   float vel;

   re_decoderCB_t mycallback;

   void _pulse(int gpio, int level, uint32_t tick);

   /* Need a static callback to link with C. */
   static void _pulseEx(int gpio, int level, uint32_t tick, void *user);


   public:

   re_decoder(int gpio, re_decoderCB_t callback);

   void re_cancel(void);

};

#endif
