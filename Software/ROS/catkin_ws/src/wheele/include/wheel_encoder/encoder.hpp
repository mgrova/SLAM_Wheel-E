#ifndef ROTARY_ENCODER_HPP
#define ROTARY_ENCODER_HPP

#include <stdint.h>
#include <cstdlib>
#include <vector>

#define SEP_MUESCAS 7.5 //Separacion en grados de las muescas del encoder
#define PI 3.14159265358979
#define NUM_TICKS 22
#define TIMEOUT_ENCD 500 
#define WDW 5


class re_decoder
{
  int mygpio, lev, lastlev, delta_t, last_t;
  double vel;
  static int no_encoders;
  int enc_timer_ID;
  std::vector<double> buffer_vel;


  void _pulse(int gpio, int level, uint32_t tick);
  void _turnOffVel(void);

  static void _pulseEx(int gpio, int level, uint32_t tick, void *user);
  static void _zeroVel(void *userdata);

  public:
    double getVel(void);

    re_decoder(int gpio);
    void re_cancel(void);

};

#endif
