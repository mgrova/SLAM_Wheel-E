#include <Arduino.h>
#include <string.h>
#include <CmdMessenger.h>

/*
ENABLE(PWM) |      A       |     B        |   STATUS           |
---------------------------------------------------------      |
     LOW    |    ----      |    ----      |MOTOR PARADO        |
     HIGH   |    HIGH      |     LOW      |MOTOR GIRA DELANTE  |
     HIGH   |    LOW       |     HIGH     |MOTOR GIRA AL REVES |
     HIGH   |    HIGH      |     HIGH     |MOTOR PARADO        |
     HIGH   |    LOW       |     LOW      |MOTOR PARADO        |
 */

/* Define the pin numbers */
#define mL_a 4
#define mL_b 2

#define m3L_en 6
#define m2L_en 5
#define m1L_en 3

#define mR_a 7
#define mR_b 8

#define m3R_en 9
#define m2R_en 10
#define m1R_en 11

bool controlling = 1; // 1 if control active & motors can run

// Attach a new CmdMessenger object to the default Serial port
CmdMessenger cmdMessenger = CmdMessenger(Serial);

enum {
  cmd_off,  // Cmd to deactivate control & motors. Reset needed after this
  change_pwm,      // Cmd to change velocities, with left motors vel and right motors vel as arguments (float32)
};

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
        digitalWrite(enable, LOW);
    }
}

void apply_pwm() {
  float m1L_pwm = cmdMessenger.readBinArg<float>(); // Front left motor pwm
  write_pwm(m1L_en, m1L_pwm, mL_a,mL_b);

  float m1R_pwm = cmdMessenger.readBinArg<float>();  // Front right motor pwm
  write_pwm(m1R_en, m1R_pwm, mR_a,mR_b);

  float m2L_pwm = cmdMessenger.readBinArg<float>(); // Mid left motor pwm
  write_pwm(m2L_en, m2L_pwm, mL_a,mL_b);

  float m2R_pwm = cmdMessenger.readBinArg<float>();  //  Mid right motor pwm
  write_pwm(m2R_en, m2R_pwm, mR_a,mR_b);

  float m3L_pwm = cmdMessenger.readBinArg<float>(); // Back left motor pwm
  write_pwm(m3L_en, m3L_pwm, mL_a,mL_b);

  float m3R_pwm = cmdMessenger.readBinArg<float>();  // Back right motor pwm
  write_pwm(m3R_en, m3R_pwm, mR_a,mR_b);
}

void turn_off() {
  controlling = ! controlling; // Turn off control and motors
}

void shutdown_motors() { // Apagar los motores
  write_pwm(m1L_en,0, mL_a,mL_b);
  write_pwm(m2L_en,0, mL_a,mL_b);
  write_pwm(m3L_en,0, mL_a,mL_b);

  write_pwm(m1R_en,0, mR_a,mR_b);
  write_pwm(m2R_en,0, mR_a,mR_b);
  write_pwm(m3R_en,0, mR_a,mR_b);
}

// Callbacks define on which received commands we take action
void attachCommandCallbacks() { // Callbacks define on which received commands we take action
  cmdMessenger.attach(cmd_off, turn_off);
  cmdMessenger.attach(change_pwm, apply_pwm);
}


void setup() {
  /* Motors pin init */
  pinMode(mL_a, OUTPUT); pinMode(mL_b, OUTPUT);
  pinMode(m1L_en, OUTPUT); pinMode(m1R_en, OUTPUT);
  pinMode(m2L_en, OUTPUT); pinMode(m2R_en, OUTPUT);
  pinMode(m3L_en, OUTPUT); pinMode(m3R_en, OUTPUT);

  Serial.begin(115200); // 115200 is the max speed on Arduino Uno

  cmdMessenger.printLfCr();  // Adds newline to every command
  attachCommandCallbacks(); // Attach my application's user-defined callback methods
}

void loop() {

  if (controlling) cmdMessenger.feedinSerialData();  // Process incoming serial data, and perform callbacks
  else shutdown_motors();  // Stop controlling and power off motors: reset needed
  //delay(1000);
}
