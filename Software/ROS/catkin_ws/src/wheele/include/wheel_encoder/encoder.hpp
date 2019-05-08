#ifndef ROTARY_ENCODER_HPP
#define ROTARY_ENCODER_HPP

#include <stdint.h>


class re_decoder
{
  
  int mygpio, lev, lastlev, delta_t, last_t;
  double vel;


  void _pulse(int gpio, int level, uint32_t tick);
  void _turnOffVel(void);
   /* Need a static callback to link with C. */
  static void _pulseEx(int gpio, int level, uint32_t tick, void *user);
  static void _zeroVel(void *userdata);

  public:
    static int no_encoders;
    int enc_timer_ID;
    double getVel(void);

    re_decoder(int gpio);
    void re_cancel(void);

};

#endif
