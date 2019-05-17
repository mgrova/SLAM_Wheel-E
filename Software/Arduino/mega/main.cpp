#include <Arduino.h>
#include <string.h>
#include <CmdMessenger.h>
#define pi 3.141592
#define pix2 6.283184  //2pi

/*
ENABLE(PWM) |      A       |     B        |   STATUS           |
--------------------------------------------------------- |
     LOW    |    ----      |    ----      |MOTOR PARADO        |
     HIGH   |    HIGH      |     LOW      |MOTOR GIRA DELANTE  |
     HIGH   |    LOW       |     HIGH     |MOTOR GIRA AL REVES |
     HIGH   |    HIGH      |     HIGH     |MOTOR PARADO        |
     HIGH   |    LOW       |     LOW      |MOTOR PARADO        |
 */

/* Define the Motors pin numbers */
#define m1L_en 4
#define m2L_en 5
#define m3L_en 6
#define m1R_en 7
#define m2R_en 8
#define m3R_en 9
// Motors directions
#define mL_a 0
#define mL_b 1
#define mR_a 14
#define mR_b 15

// Define the encoders pin numbers
#define m1l_encoder 2 //INTF0
#define m2l_encoder 3 //INTF1
#define m3l_encoder 18  //INTF5
#define m1r_encoder 19  //INTF4
#define m2r_encoder 20  //INTF3
#define m3r_encoder 21  //INTF2
// Encoders data
#define slits_arc 7.5 // Grades between slits
#define number_slits 22

/*
void encoder_isr_on(){
  attachInterrupt(digitalPinToInterrupt(m1l_encoder), m1l_isr, RISING);
  attachInterrupt(digitalPinToInterrupt(m1r_encoder), m1r_isr, RISING);
  attachInterrupt(digitalPinToInterrupt(m2l_encoder), m2l_isr, RISING);
  attachInterrupt(digitalPinToInterrupt(m2r_encoder), m2r_isr, RISING);
  attachInterrupt(digitalPinToInterrupt(m3l_encoder), m3l_isr, RISING);
  attachInterrupt(digitalPinToInterrupt(m3r_encoder), m3r_isr, RISING);
}

void encoder_isr_off(){
  detachInterrupt(digitalPinToInterrupt(m1l_encoder));
  detachInterrupt(digitalPinToInterrupt(m1r_encoder));
  detachInterrupt(digitalPinToInterrupt(m2l_encoder));
  detachInterrupt(digitalPinToInterrupt(m2r_encoder));
  detachInterrupt(digitalPinToInterrupt(m3l_encoder));
  detachInterrupt(digitalPinToInterrupt(m3r_encoder));
}*/

volatile boolean m1l_first,m1l_triggered,m2l_first,m2l_triggered,m3l_first,m3l_triggered;
volatile boolean m1r_first,m1r_triggered,m2r_first,m2r_triggered,m3r_first,m3r_triggered;
volatile unsigned long m1l_startTime, m1l_finishTime,m2l_startTime, m2l_finishTime,m3l_startTime, m3l_finishTime;
volatile unsigned long m1r_startTime, m1r_finishTime,m2r_startTime, m2r_finishTime,m3r_startTime, m3r_finishTime;
volatile unsigned long overflowCount;

ISR (TIMER1_OVF_vect) { // timer overflows (every 65536 counts)
  overflowCount++;
}  // end of TIMER1_OVF_vect

void m1l_isr () {
  unsigned int counter = TCNT2;  // quickly save it

  // wait until we noticed last one
  if (m1l_triggered)
    return;

  if (m1l_first){
    m1l_startTime = (overflowCount << 16) + counter;
    m1l_first= false;
    return;
  }

  m1l_finishTime = (overflowCount << 16) + counter;
  m1l_triggered = true;
  detachInterrupt(digitalPinToInterrupt(m1l_encoder));
}  // end of isr
void m2l_isr () {
  unsigned int counter = TCNT2;  // quickly save it

  // wait until we noticed last one
  if (m2l_triggered)
    return;

  if (m2l_first){
    m2l_startTime = (overflowCount << 16) + counter;
    m2l_first= false;
    return;
  }

  m2l_finishTime = (overflowCount << 16) + counter;
  m2l_triggered = true;
  detachInterrupt(digitalPinToInterrupt(m2l_encoder));
}  // end of isr
void m3l_isr () {
  unsigned int counter = TCNT2;  // quickly save it

  // wait until we noticed last one
  if (m3l_triggered)
    return;

  if (m3l_first){
    m3l_startTime = (overflowCount << 16) + counter;
    m3l_first= false;
    return;
  }

  m3l_finishTime = (overflowCount << 16) + counter;
  m3l_triggered = true;
  detachInterrupt(digitalPinToInterrupt(m3l_encoder));
}  // end of isr
void m1r_isr () {
  unsigned int counter = TCNT2;  // quickly save it

  // wait until we noticed last one
  if (m1r_triggered)
    return;

  if (m1r_first){
    m1r_startTime = (overflowCount << 16) + counter;
    m1r_first= false;
    return;
  }

  m1r_finishTime = (overflowCount << 16) + counter;
  m1r_triggered = true;
  detachInterrupt(digitalPinToInterrupt(m1r_encoder));
}  // end of isr
void m2r_isr () {
  unsigned int counter = TCNT2;  // quickly save it

  // wait until we noticed last one
  if (m2r_triggered)
    return;

  if (m2r_first){
    m2r_startTime = (overflowCount << 16) + counter;
    m2r_first= false;
    return;
  }

  m2r_finishTime = (overflowCount << 16) + counter;
  m2r_triggered = true;
  detachInterrupt(digitalPinToInterrupt(m2r_encoder));
}  // end of isr
void m3r_isr () {
  unsigned int counter = TCNT2;  // quickly save it

  // wait until we noticed last one
  if (m3r_triggered)
    return;

  if (m3r_first){
    m3r_startTime = (overflowCount << 16) + counter;
    m3r_first= false;
    return;
  }

  m3r_finishTime = (overflowCount << 16) + counter;
  m3r_triggered = true;
  detachInterrupt(digitalPinToInterrupt(m3r_encoder));
}  // end of isr

void setup_m1l_isr(){ // get ready for next time
  EIFR = bit (INTF0);  // clear flag for interrupt 0
  m1l_first = true;
  m1l_triggered = false;  // re-arm for next time
  attachInterrupt(digitalPinToInterrupt(m1l_encoder), m1l_isr, RISING);
}  // end of prepareForInterrupts
void setup_m2l_isr(){ // get ready for next time
  EIFR = bit (INTF1);  // clear flag for interrupt 0
  m2l_first = true;
  m2l_triggered = false;  // re-arm for next time
  attachInterrupt(digitalPinToInterrupt(m2l_encoder), m2l_isr, RISING);
}
void setup_m3l_isr(){ // get ready for next time
  EIFR = bit (INTF5);  // clear flag for interrupt 0
  m3l_first = true;
  m3l_triggered = false;  // re-arm for next time
  attachInterrupt(digitalPinToInterrupt(m3l_encoder), m3l_isr, RISING);
}
void setup_m1r_isr(){ // get ready for next time
  EIFR = bit (INTF4);  // clear flag for interrupt 0
  m1r_first = true;
  m1r_triggered = false;  // re-arm for next time
  attachInterrupt(digitalPinToInterrupt(m1r_encoder), m1r_isr, RISING);
}
void setup_m2r_isr(){ // get ready for next time
  EIFR = bit (INTF3);  // clear flag for interrupt 0
  m2r_first = true;
  m2r_triggered = false;  // re-arm for next time
  attachInterrupt(digitalPinToInterrupt(m2r_encoder), m2r_isr, RISING);
}
void setup_m3r_isr(){ // get ready for next time
  EIFR = bit (INTF2);  // clear flag for interrupt 0
  m3r_first = true;
  m3r_triggered = false;  // re-arm for next time
  attachInterrupt(digitalPinToInterrupt(m3r_encoder), m3r_isr, RISING);
}
void setup_isr(){
  setup_m1l_isr();
  setup_m2l_isr();
  setup_m3l_isr();
  setup_m1r_isr();
  setup_m2r_isr();
  setup_m3r_isr();
}

/* function to write pwm 2 motors & manage directions */
void write_pwm(int enable,int pwm, int dir1, int dir2){
    if(pwm > 0){
      if (pwm>255) pwm=255;
        digitalWrite(dir1, HIGH);
        digitalWrite(dir2, LOW);
        analogWrite(enable, pwm);
    }
    else if(pwm < 0){
      if (pwm<-255) pwm=-255;
        digitalWrite(dir1, LOW);
        digitalWrite(dir2, HIGH);
        analogWrite(enable, abs(pwm));
    }
    else{
        //digitalWrite(dir1, LOW);
        //digitalWrite(dir2, LOW);
        digitalWrite(enable, LOW);
    }
}

unsigned long kp,ki;
static float sat_err_m1l,i_m1l,sat_err_m2l,i_m2l,sat_err_m3l,i_m3l;
static float sat_err_m1r,i_m1r,sat_err_m2r,i_m2r,sat_err_m3r,i_m3r;

float control_law(int m, float ref, float out, float i,float sat_err){
  float sat_err_integrated, ek, ukns, ukreal, p;
  sat_err_integrated=(float)sat_err*0.016393;  // Integration of how much we satured
  ek = (float)ref-(float)out;  // Error = Desired - Actual(output)
  p = kp*ek;
  i = ki*(i+ek*0.016393);
  //d = kd*((ek-ek1)*61.0);
  ukns=p+i+(sat_err_integrated/0.1);//+d
  if(ukns<-255) ukreal=-255.0;  // Saturation
  else if(ukns>255) ukreal=255.0;
  else ukreal=ukns;
  sat_err=ukreal-ukns;  // Saturation error
  //ek1=ek; // Error update
  switch(m){  // Store saturation error, integral term & (just if derivative effect is used) error
    case 1:
      sat_err_m1l=sat_err;
      i_m1l=i;
      //ek1_m1l=ek1;
      break;
    case 2:
      sat_err_m1r=sat_err;
      i_m1r=i;
      //ek1_m1l=ek1;
      break;
    case 3:
      sat_err_m2l=sat_err;
      i_m2l=i;
      //ek1_m2l=ek1;
      break;
    case 4:
      sat_err_m2r=sat_err;
      i_m2r=i;
      //ek1_m2r=ek1;
      break;
    case 5:
      sat_err_m3l=sat_err;
      i_m3l=i;
      //ek1_m3l=ek1;
      break;
    case 6:
      sat_err_m3r=sat_err;
      i_m3r=i;
      //ek1_m3r=ek1;
      break;
  }
  return ukreal;
}


void shutdown_motors() { // Apagar los motores
  write_pwm(m1L_en,0, mL_a,mL_b);
  write_pwm(m2L_en,0, mL_a,mL_b);
  write_pwm(m3L_en,0, mL_a,mL_b);

  write_pwm(m1R_en,0, mR_a,mR_b);
  write_pwm(m2R_en,0, mR_a,mR_b);
  write_pwm(m3R_en,0, mR_a,mR_b);
}


bool controlling = 1; // 1 if control active & motors can run
CmdMessenger cmdMessenger = CmdMessenger(Serial); // Attach a new CmdMessenger object to the default Serial port

enum {
  cmd_off,  // Cmd to deactivate control & motors. Reset needed after this
  receive_ref,
  send_encoder,
};

void turn_off() {
  controlling = ! controlling; // Turn off control and motors
}

float left_ref, right_ref;

void take_ref(){
  left_ref = cmdMessenger.readBinArg<float>();
  right_ref = cmdMessenger.readBinArg<float>();
  //we could act here (?)
}


void attachCommandCallbacks() { // Callbacks define on which received commands we take action
  cmdMessenger.attach(cmd_off, turn_off);
  cmdMessenger.attach(receive_ref, take_ref);
  cmdMessenger.attach(send_encoder)
  cmdMessenger.attach(send_control_sig)
}


void setup() {
  // reset Timer 2
  TCCR2A = 0;
  TCCR2B = 0;
  // Timer 2 - interrupt on overflow
  TIMSK2 = bit (TOIE2);   // enable Timer2 Interrupt
  // zero it
  TCNT2 = 0;
  overflowCount = 0;
  // start Timer 2
  TCCR2B =  bit (CS10);  //  no prescaling

  // Encoders pins init
  pinMode(m1l_encoder, INPUT); pinMode(m2l_encoder, INPUT); pinMode(m3l_encoder, INPUT);
  pinMode(m1r_encoder, INPUT); pinMode(m2r_encoder, INPUT); pinMode(m3r_encoder, INPUT);

  /* Motors pin init */
  pinMode(mL_a, OUTPUT); pinMode(mL_b, OUTPUT);
  pinMode(m1L_en, OUTPUT); pinMode(m1R_en, OUTPUT);
  pinMode(m2L_en, OUTPUT); pinMode(m2R_en, OUTPUT);
  pinMode(m3L_en, OUTPUT); pinMode(m3R_en, OUTPUT);

  Serial.begin(115200); // 115200 is the max speed on Arduino Uno

  cmdMessenger.printLfCr();  // Adds newline to every command
  attachCommandCallbacks(); // Attach my application's user-defined callback methods

  setup_isr();
}

void loop() {
  float m1l_rads,m2l_rads,m3l_rads,m1r_rads,m2r_rads,m3r_rads;
  float m1l_pwm,m2l_pwm,m3l_pwm,m1r_pwm,m2r_pwm,m3r_pwm;

  if (controlling) {
    if (m1l_triggered) {
      unsigned long elapsedTime = m1l_finishTime - m1l_startTime;
      m1l_rads = ((float)slits_arc/((float)elapsedTime*62.5))*((float)pix2/(float)360.0);  // each tick is 62.5 ns at 16 MHz
    }
    if (m1r_triggered) {
      unsigned long elapsedTime = m1r_finishTime - m1r_startTime;
      m1r_rads = ((float)slits_arc/((float)elapsedTime*62.5))*((float)pix2/(float)360.0);  // each tick is 62.5 ns at 16 MHz
    }
    if (m2l_triggered) {
      unsigned long elapsedTime = m2l_finishTime - m2l_startTime;
      m2l_rads = ((float)slits_arc/((float)elapsedTime*62.5))*((float)pix2/(float)360.0);  // each tick is 62.5 ns at 16 MHz
    }
    if (m2r_triggered) {
      unsigned long elapsedTime = m2r_finishTime - m2r_startTime;
      m2r_rads = ((float)slits_arc/((float)elapsedTime*62.5))*((float)pix2/(float)360.0);  // each tick is 62.5 ns at 16 MHz
    }
    if (m3l_triggered) {
      unsigned long elapsedTime = m3l_finishTime - m3l_startTime;
      m3l_rads = ((float)slits_arc/((float)elapsedTime*62.5))*((float)pix2/(float)360.0);  // each tick is 62.5 ns at 16 MHz
    }
    if (m3r_triggered) {
      unsigned long elapsedTime = m3r_finishTime - m3r_startTime;
      m3r_rads = ((float)slits_arc/((float)elapsedTime*62.5))*((float)pix2/(float)360.0);  // each tick is 62.5 ns at 16 MHz
    }

    if ((m1l_triggered) && (m2l_triggered) && (m3l_triggered) && (m1r_triggered) && (m2r_triggered) && (m3r_triggered)) {
      cmdMessenger.feedinSerialData();  // Process incoming serial data, and perform callbacks
      //Compute control
      m1l_pwm=control_law(1,left_ref,m1l_rads,i_m1l,sat_err_m1l);
      m1r_pwm=control_law(2,right_ref,m1r_rads,i_m1r,sat_err_m1r);
      m2l_pwm=control_law(3,left_ref,m2l_rads,i_m2l,sat_err_m2l);
      m2r_pwm=control_law(4,right_ref,m2r_rads,i_m2r,sat_err_m2r);
      m3l_pwm=control_law(5,left_ref,m3l_rads,i_m3l,sat_err_m3l);
      m3r_pwm=control_law(6,right_ref,m3r_rads,i_m3r,sat_err_m3r);
      //Act
      write_pwm(m1L_en,m1l_pwm, mL_a,mL_b);
      write_pwm(m2L_en,m2l_pwm, mL_a,mL_b);
      write_pwm(m3L_en,m3l_pwm, mL_a,mL_b);
      write_pwm(m1R_en,m1r_pwm, mR_a,mR_b);
      write_pwm(m2R_en,m2r_pwm, mR_a,mR_b);
      write_pwm(m3R_en,m3r_pwm, mR_a,mR_b);

      
      //Send rad/s
      float vector_rads[6]={m1l_rads,m2l_rads,m3l_rads,m1r_rads,m2r_rads,m3r_rads};
      float vector_pwm[6]={m1l_pwm,m2l_pwm,m3l_pwm,m1r_pwm,m2r_pwm,m3r_pwm};

      cmdMessenger.sendBinCmd(send_encoder,vector_rads)
      CmdMessenger.sendBinCmd(send_control_sig,vector_pwm)
      // Turn on encoders interrupts again
      setup_isr();
    }
  }
  else shutdown_motors();  // Stop controlling and power off motors: reset needed
}
