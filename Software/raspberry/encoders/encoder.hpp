#ifndef ROTARY_ENCODER_HPP
#define ROTARY_ENCODER_HPP

#include <stdint.h>
#include <ctime.h>

typedef void (*re_decoderCB_t)(int);

/*TODO programar contadores, inicializarlos en el constructor, etc*/ 
class re_decoder
{
   int mygpio, lev, lastlev;

   re_decoderCB_t mycallback;

   void _pulse(int gpio, int level, uint32_t tick);

   /* Need a static callback to link with C. */
   static void _pulseEx(int gpio, int level, uint32_t tick, void *user);


   public:

   re_decoder(int gpio, re_decoderCB_t callback);
   /*
      This function establishes a rotary encoder on gpioA and gpioB.

      When the encoder is turned the callback function is called.
   */

   void re_cancel(void);
   /*
      This function releases the resources used by the decoder.
   */
};

#endif
