#include <Arduino.h>
#include <string.h>
#include <CmdMessenger.h>
#define pi 3.141592
#define pix2 6.283184  //2pi
#define t_cntl 0.016383 //seconds = 16.383ms = 61Hz

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
#define m1l_encoder 2 //INTF4
#define m2l_encoder 3 //INTF5
#define m3l_encoder 18  //INTF3
#define m1r_encoder 19  //INTF2
#define m2r_encoder 20  //INTF1
#define m3r_encoder 21  //INTF0
// Encoders data
#define slits_arc 7.5 // Grades between slits
#define number_slits 22

//Debug purpose leds
#define led1 23
#define led2 22

/* INTERRUPTS & TIMERS
Timer 2: 8bit timer with overflow interrupt for account time
Timer 1: 16bit timer that provides synchronous control (prescle & max configured in setup)
m1l_isr(): Rising edge interrupt that save time to compute rad/s
*/
volatile boolean m1l_first,m1l_triggered,m2l_first,m2l_triggered,m3l_first,m3l_triggered;
volatile boolean m1r_first,m1r_triggered,m2r_first,m2r_triggered,m3r_first,m3r_triggered;
volatile unsigned long m1l_startTime, m1l_finishTime,m2l_startTime, m2l_finishTime,m3l_startTime, m3l_finishTime;
volatile unsigned long m1r_startTime, m1r_finishTime,m2r_startTime, m2r_finishTime,m3r_startTime, m3r_finishTime;
volatile unsigned long overflowCount;
volatile bool flag_cntl;
volatile bool flag_serial;

ISR (TIMER2_OVF_vect) { // timer overflows (every 65536 counts)
  overflowCount++;
}  // end of TIMER1_OVF_vect

ISR( TIMER1_COMPA_vect){
  flag_cntl = true;
  flag_serial=true;
  TIMSK1=0;
}

void m1l_isr () {
  unsigned int counter = TCNT2;  // quickly save it
  // wait until we noticed last one
  if (m1l_triggered)
    return;
  if (m1l_first){
    m1l_startTime = (overflowCount << 8) + counter;
    m1l_first= false;
    return;
  }
  m1l_finishTime = (overflowCount << 8) + counter;
  m1l_triggered = true;
  detachInterrupt(digitalPinToInterrupt(m1l_encoder));
}  // end of isr
void m2l_isr () {
  unsigned int counter = TCNT2;  // quickly save it
  // wait until we noticed last one
  if (m2l_triggered)
    return;
  if (m2l_first){
    m2l_startTime = (overflowCount << 8) + counter;
    m2l_first= false;
    return;
  }
  m2l_finishTime = (overflowCount << 8) + counter;
  m2l_triggered = true;
  detachInterrupt(digitalPinToInterrupt(m2l_encoder));
}  // end of isr
void m3l_isr () {
  unsigned int counter = TCNT2;  // quickly save it
  // wait until we noticed last one
  if (m3l_triggered)
    return;
  if (m3l_first){
    m3l_startTime = (overflowCount << 8) + counter;
    m3l_first= false;
    return;
  }
  m3l_finishTime = (overflowCount << 8) + counter;
  m3l_triggered = true;
  detachInterrupt(digitalPinToInterrupt(m3l_encoder));
}  // end of isr
void m1r_isr () {
  unsigned int counter = TCNT2;  // quickly save it
  // wait until we noticed last one
  if (m1r_triggered)
    return;
  if (m1r_first){
    m1r_startTime = (overflowCount << 8) + counter;
    m1r_first= false;
    return;
  }
  m1r_finishTime = (overflowCount << 8) + counter;
  m1r_triggered = true;
  detachInterrupt(digitalPinToInterrupt(m1r_encoder));
}  // end of isr
void m2r_isr () {
  unsigned int counter = TCNT2;  // quickly save it
  // wait until we noticed last one
  if (m2r_triggered)
    return;
  if (m2r_first){
    m2r_startTime = (overflowCount << 8) + counter;
    m2r_first= false;
    return;
  }
  m2r_finishTime = (overflowCount << 8) + counter;
  m2r_triggered = true;
  detachInterrupt(digitalPinToInterrupt(m2r_encoder));
}  // end of isr
void m3r_isr () {
  unsigned int counter = TCNT2;  // quickly save it
  // wait until we noticed last one
  if (m3r_triggered)
    return;
  if (m3r_first){
    m3r_startTime = (overflowCount << 8) + counter;
    m3r_first= false;
    return;
  }
  m3r_finishTime = (overflowCount << 8) + counter;
  m3r_triggered = true;
  detachInterrupt(digitalPinToInterrupt(m3r_encoder));
}  // end of isr

void setup_m1l_isr(){ // get ready for next time
  EIFR = bit (INTF4);  // clear flag for interrupt 0
  m1l_first = true;
  m1l_triggered = false;  // re-arm for next time
  attachInterrupt(digitalPinToInterrupt(m1l_encoder), m1l_isr, RISING);
}  // end of prepareForInterrupts
void setup_m2l_isr(){ // get ready for next time
  EIFR = bit (INTF5);  // clear flag for interrupt 0
  m2l_first = true;
  m2l_triggered = false;  // re-arm for next time
  attachInterrupt(digitalPinToInterrupt(m2l_encoder), m2l_isr, RISING);
}
void setup_m3l_isr(){ // get ready for next time
  EIFR = bit (INTF3);  // clear flag for interrupt 0
  m3l_first = true;
  m3l_triggered = false;  // re-arm for next time
  attachInterrupt(digitalPinToInterrupt(m3l_encoder), m3l_isr, RISING);
}
void setup_m1r_isr(){ // get ready for next time
  EIFR = bit (INTF2);  // clear flag for interrupt 0
  m1r_first = true;
  m1r_triggered = false;  // re-arm for next time
  attachInterrupt(digitalPinToInterrupt(m1r_encoder), m1r_isr, RISING);
}
void setup_m2r_isr(){ // get ready for next time
  EIFR = bit (INTF1);  // clear flag for interrupt 0
  m2r_first = true;
  m2r_triggered = false;  // re-arm for next time
  attachInterrupt(digitalPinToInterrupt(m2r_encoder), m2r_isr, RISING);
}
void setup_m3r_isr(){ // get ready for next time
  EIFR = bit (INTF0);  // clear flag for interrupt 0
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

/* ACTION & CONTROL STUFF
-No hay Kp y Ki para cada motor es cuestion de añadir otro switch como en control.cpp
+Antiwindup 4
+ It should be runned without interrupts (as serial stuff)
*/

void write_pwm(int enable,int pwm, int dir1, int dir2){ //function to write pwm 2 motors & manage directions

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
        digitalWrite(enable, LOW);
    }
}

unsigned long kp=13.0,ki=0.9;
static float sat_err_m1l,i_m1l,sat_err_m2l,i_m2l,sat_err_m3l,i_m3l;
static float sat_err_m1r,i_m1r,sat_err_m2r,i_m2r,sat_err_m3r,i_m3r;

float control_law(int m, float ref, float out, float i,float sat_err, float sample_time){
  float sat_err_integrated, ek, ukns, ukreal, p;
  sat_err_integrated=(float)sat_err*sample_time;  // Integration of how much we satured
  ek = (float)ref-(float)out;  // Error = Desired - Actual(output)
  p = kp*ek;
  i = ki*(i+ek*sample_time);
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

/*  SERIAL STUFF
https://github.com/thijse/Arduino-CmdMessenger
https://github.com/zivlab/PyCmdMessenger
+ It should be used without interrupts on, bc it uses some of thems (idk which ones)
+ Tenemos todos los comandos que ves en enum
      cmd_off: para todo
      receive_ref: take reference in rad/s from pc
      send_encoder: send all 6 encoders data in rad/s to pc
      send_control_sig: send 6 pwm written to motors to pc
      change_kp: take kp from pc
      change_ki:
      request_ticks: if this cmd is received, send encoders data
      request_control_signal:
+ Example in cmd_serial_example
*/
bool controlling = 1; // 1 if control active & motors can run
CmdMessenger cmdMessenger = CmdMessenger(Serial); // Attach a new CmdMessenger object to the default Serial port
enum {
  cmd_off,  // Cmd to deactivate control & motors. Reset needed after this
  receive_ref,
  send_encoder,
  send_control_sig,
  change_kp,
  change_ki,
  request_ticks,
  request_control_signal,
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
void on_change_kp(){
  kp = cmdMessenger.readBinArg<float>();
}
void on_change_ki(){
  ki = cmdMessenger.readBinArg<float>();
}
float m1l_rads=0,m2l_rads=0,m3l_rads=0,m1r_rads=0,m2r_rads=0,m3r_rads=0;
float m1l_pwm=0,m2l_pwm=0,m3l_pwm=0,m1r_pwm=0,m2r_pwm=0,m3r_pwm=0;
void on_request_ticks(){
  cmdMessenger.sendCmdStart(send_encoder);
  cmdMessenger.sendCmdBinArg(m1l_rads); cmdMessenger.sendCmdBinArg(m2l_rads); cmdMessenger.sendCmdBinArg(m3l_rads);
  cmdMessenger.sendCmdBinArg(m1r_rads); cmdMessenger.sendCmdBinArg(m2r_rads); cmdMessenger.sendCmdBinArg(m3r_rads);
  cmdMessenger.sendCmdEnd();
}
void on_request_control_signal(){
  cmdMessenger.sendCmdStart(send_control_sig);
  cmdMessenger.sendCmdBinArg(m1l_pwm); cmdMessenger.sendCmdBinArg(m2l_pwm); cmdMessenger.sendCmdBinArg(m3l_pwm);
  cmdMessenger.sendCmdBinArg(m1r_pwm); cmdMessenger.sendCmdBinArg(m2r_pwm); cmdMessenger.sendCmdBinArg(m3r_pwm);
  cmdMessenger.sendCmdEnd();
}
void attachCommandCallbacks() { // Callbacks define on which received commands we take action
  cmdMessenger.attach(cmd_off, turn_off);
  cmdMessenger.attach(receive_ref, take_ref);
  cmdMessenger.attach(change_kp, on_change_kp);
  cmdMessenger.attach(change_ki, on_change_ki);
  cmdMessenger.attach(request_ticks, on_request_ticks);
  cmdMessenger.attach(request_control_signal, on_request_control_signal);
}


void setup() {
  Serial.begin(115200); // 115200 is the max speed on Arduino Uno
  cmdMessenger.printLfCr();  // Adds newline to every command
  attachCommandCallbacks();  // Attach my application's user-defined callback methods

  // reset Timer 1
  TCCR1A = 0;
  TCCR1B = 0;
  // zero it
  TCNT1 = 0;
  // start Timer 1
  OCR1A  = 255; //Count 255 cycles (prescaled with...)
  TCCR1B =  bit (WGM12) | bit (CS12) | bit (CS10);  //  1024 prescale

  // reset Timer 2
  TCCR2A = 0;
  TCCR2B = 0;
  // zero it
  TCNT2 = 0;
  overflowCount = 0;
  // start Timer 2
  TCCR2B =  bit (CS10);  //  no prescaling

  //Debug leds
  pinMode(led1,OUTPUT);
  digitalWrite(led1,LOW);
  pinMode(led2,OUTPUT);
  digitalWrite(led2,LOW);

  // Encoders pins init
  pinMode(m1l_encoder, INPUT); pinMode(m2l_encoder, INPUT); pinMode(m3l_encoder, INPUT);
  pinMode(m1r_encoder, INPUT); pinMode(m2r_encoder, INPUT); pinMode(m3r_encoder, INPUT);

  /* Motors pin init */
  pinMode(mL_a, OUTPUT);   pinMode(mL_b, OUTPUT);
  pinMode(m1L_en, OUTPUT); pinMode(m1R_en, OUTPUT);
  pinMode(m2L_en, OUTPUT); pinMode(m2R_en, OUTPUT);
  pinMode(m3L_en, OUTPUT); pinMode(m3R_en, OUTPUT);

  // Timer 2 - interrupt on overflow
  TIMSK2 = bit (TOIE2);   // enable Timer2 Interrupt
  // Timer 1 - interrupt on compare
  TIMSK1 = bit (OCIE1A);   // enable Timer1 Interrupt
  setup_isr();
}

void loop() {
  if (controlling) {
    if (m1l_triggered) {
      unsigned long elapsedTime = m1l_finishTime - m1l_startTime;
      digitalWrite(led1,HIGH);
      digitalWrite(led2,LOW);//debug
      m1l_rads = ((float)0.28/((float)elapsedTime*0.0000000625));  // each tick is 62.5 ns at 16 MHz
      setup_m1l_isr();
    } //else m1l_rads = 0.0;
    if (m1r_triggered) {
      digitalWrite(led1,LOW);
      digitalWrite(led2,HIGH);//debug
      unsigned long elapsedTime = m1r_finishTime - m1r_startTime;
      m1r_rads = ((float)0.28/((float)elapsedTime*0.0000000625));  // each tick is 62.5 ns at 16 MHz
      setup_m1r_isr();
    } //else m1r_rads = 0.0;
    if (m2l_triggered) {
      unsigned long elapsedTime = m2l_finishTime - m2l_startTime;
      m2l_rads = ((float)4480000.0/(float)elapsedTime);  // each tick is 62.5 ns at 16 MHz
      setup_m2l_isr();
    } //else m2l_rads = 0.0;
    if (m2r_triggered) {
      unsigned long elapsedTime = m2r_finishTime - m2r_startTime;
      m2r_rads = ((float)4480000.0/(float)elapsedTime);  // each tick is 62.5 ns at 16 MHz
      setup_m2l_isr();
    } //else m2r_rads = 0.0;
    if (m3l_triggered) {
      digitalWrite(led1,LOW);
      digitalWrite(led2,LOW);//debug
      unsigned long elapsedTime = m3l_finishTime - m3l_startTime;
      m3l_rads = ((float)4480000.0/(float)elapsedTime);  // each tick is 62.5 ns at 16 MHz
      setup_m3l_isr();
    } //else m3l_rads = 0.0;
    if (m3r_triggered) {
      digitalWrite(led1,HIGH);
      digitalWrite(led2,HIGH);//debug
      unsigned long elapsedTime = m3r_finishTime - m3r_startTime;
      m3r_rads = ((float)0.28/((float)elapsedTime*0.0000000625));  // each tick is 62.5 ns at 16 MHz
      setup_m3r_isr();
    } //else m3r_rads = 0.0;

    if (flag_cntl){ //Compute control
      m1l_pwm=control_law(1,left_ref,m1l_rads,i_m1l,sat_err_m1l,t_cntl);
      m1r_pwm=control_law(2,right_ref,m1r_rads,i_m1r,sat_err_m1r,t_cntl);
      m2l_pwm=control_law(3,left_ref,m2l_rads,i_m2l,sat_err_m2l,t_cntl);
      m2r_pwm=control_law(4,right_ref,m2r_rads,i_m2r,sat_err_m2r,t_cntl);
      m3l_pwm=control_law(5,left_ref,m3l_rads,i_m3l,sat_err_m3l,t_cntl);
      m3r_pwm=0;//m3r_pwm=control_law(6,right_ref,m3r_rads,i_m3r,sat_err_m3r,t_cntl);
    //Act
      write_pwm(m1L_en,m1l_pwm, mL_a,mL_b);
      write_pwm(m2L_en,m2l_pwm, mL_a,mL_b);
      write_pwm(m3L_en,m3l_pwm, mL_a,mL_b);
      write_pwm(m1R_en,m1r_pwm, mR_a,mR_b);
      write_pwm(m2R_en,m2r_pwm, mR_a,mR_b);
      //write_pwm(m3R_en,m3r_pwm, mR_a,mR_b);
    //Serial stuff
      detachInterrupt(digitalPinToInterrupt(m1l_encoder));
      detachInterrupt(digitalPinToInterrupt(m2l_encoder));
      detachInterrupt(digitalPinToInterrupt(m3l_encoder));
      detachInterrupt(digitalPinToInterrupt(m1r_encoder));
      detachInterrupt(digitalPinToInterrupt(m2r_encoder));
      detachInterrupt(digitalPinToInterrupt(m3r_encoder));
      TIMSK2 = 0; //overflow interrumpt off
      on_request_ticks();
      on_request_control_signal();
      cmdMessenger.feedinSerialData();  // Process incoming serial data, and perform
      TIMSK2 = bit (TOIE2);   // enable Timer2 overflow Interrupt
      attachInterrupt(digitalPinToInterrupt(m1l_encoder), m1l_isr, RISING);
      attachInterrupt(digitalPinToInterrupt(m2l_encoder), m2l_isr, RISING);
      attachInterrupt(digitalPinToInterrupt(m3l_encoder), m3l_isr, RISING);
      attachInterrupt(digitalPinToInterrupt(m1r_encoder), m1r_isr, RISING);
      attachInterrupt(digitalPinToInterrupt(m2r_encoder), m2r_isr, RISING);
      attachInterrupt(digitalPinToInterrupt(m3r_encoder), m3r_isr, RISING);
      flag_cntl=false;
      TIMSK1 = bit (OCIE1A);   // enable Timer1 Interrupt
    }
    /*if ((m1l_triggered) && (m2l_triggered) && (m3l_triggered) && (m1r_triggered) && (m2r_triggered) && (m3r_triggered) && flag_serial) {
      digitalWrite(led1,HIGH); //DEBUG
      TIMSK2 = 0; //overflow interrumpt off
      TIMSK1 = 0;
      on_request_ticks();
      on_request_control_signal();
      cmdMessenger.feedinSerialData();  // Process incoming serial data, and perform
      TIMSK2 = bit (TOIE2);   // enable Timer2 overflow Interrupt
      TIMSK1 = bit (OCIE1A);   // enable Timer1 Interrupt
      flag_serial=false;
    }*/
    /*if ((m1l_triggered) && (m2l_triggered) && (m3l_triggered) && (m1r_triggered) && (m2r_triggered) && (m3r_triggered)) {
      setup_isr();
    }*/
  } else shutdown_motors();  // Stop controlling and power off motors: reset needed
}
