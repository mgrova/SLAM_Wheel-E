#include <Arduino.h>
#include <string.h>
#include <CmdMessenger.h>

//Debug purpose leds
#define led1 23


bool controlling = 1; // 1 if control active & motors can run
CmdMessenger cmdMessenger = CmdMessenger(Serial); // Attach a new CmdMessenger object to the default Serial port

enum {
  cmd_off,  // Cmd to deactivate control & motors. Reset needed after this
  receive_ref,
  send_encoder,
  send_control_sig
};

void turn_off() {
  controlling = ! controlling; // Turn off control and motors
}

float left_ref=0, right_ref=0;

void take_ref(){
  left_ref = cmdMessenger.readBinArg<float>();
  right_ref = cmdMessenger.readBinArg<float>();
  //we could act here (?)
}

void attachCommandCallbacks() { // Callbacks define on which received commands we take action
  cmdMessenger.attach(cmd_off, turn_off);
  cmdMessenger.attach(receive_ref, take_ref);
}


void setup() {
  //Debug leds
  pinMode(led1,OUTPUT);
  digitalWrite(led1,LOW);

  Serial.begin(115200); // 115200 is the max speed on Arduino Uno

  cmdMessenger.printLfCr();  // Adds newline to every command
  attachCommandCallbacks();  // Attach my application's user-defined callback methods
}

float m1l_rads=1,m2l_rads=2,m3l_rads=3,m1r_rads=0,m2r_rads=0,m3r_rads=0;
float m1l_pwm=6,m2l_pwm=7,m3l_pwm=8,m1r_pwm=0,m2r_pwm=0,m3r_pwm=0;

void loop() {
  if (controlling) {
      m1l_rads++;
      //digitalWrite(led1,HIGH); //DEBUG
      cmdMessenger.feedinSerialData();  // Process incoming serial data, and perform callbacks
      //Send rad/s
      float vector_rads[6]={m1l_rads,m2l_rads,m3l_rads,m1r_rads,m2r_rads,m3r_rads};
      float vector_pwm[6]={m1l_pwm,m2l_pwm,m3l_pwm,m1r_pwm,m2r_pwm,m3r_pwm};
      cmdMessenger.sendCmdStart(send_encoder);
      cmdMessenger.sendCmdBinArg(m1l_rads); cmdMessenger.sendCmdBinArg(m2l_rads); cmdMessenger.sendCmdBinArg(m3l_rads);
      cmdMessenger.sendCmdBinArg(m1r_rads); cmdMessenger.sendCmdBinArg(m3r_rads); cmdMessenger.sendCmdBinArg(m3r_rads);
      cmdMessenger.sendCmdEnd();
      cmdMessenger.sendCmdStart(send_control_sig);
      cmdMessenger.sendCmdBinArg(m1l_pwm); cmdMessenger.sendCmdBinArg(m2l_pwm); cmdMessenger.sendCmdBinArg(m3l_pwm);
      cmdMessenger.sendCmdBinArg(m1r_pwm); cmdMessenger.sendCmdBinArg(m3r_pwm); cmdMessenger.sendCmdBinArg(m3r_pwm);
      cmdMessenger.sendCmdEnd();
      delay(500);
  }
}
