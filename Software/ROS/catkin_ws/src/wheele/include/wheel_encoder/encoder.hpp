#ifndef ROTARY_ENCODER_HPP
#define ROTARY_ENCODER_HPP

#include <stdint.h>


class re_decoder
{
  
  int mygpio, lev, lastlev, delta_t, last_t, enc_timer_ID;
  float vel;


  void _pulse(int gpio, int level, uint32_t tick);

   /* Need a static callback to link with C. */
  static void _pulseEx(int gpio, int level, uint32_t tick, void *user);
  static void _zeroVel(void *userdata);

  public:
    static int no_encoders;
    float getVel(void);

    re_decoder(int gpio);
    void re_cancel(void);

};

#endif
