#include <Arduino.h>
#include <string.h>
#include <CmdMessenger.h>

/*
ENABLE(PWM) |      A       |     B        |   STATUS           |
--------------------------------------------------------- |
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
  change_vel,      // Cmd to change velocities, with left motors vel and right motors vel as arguments (float32)
};

/* function to control motor */
void control_motor(int enable,int speed, int dir1, int dir2){
    if(speed > 0){
        digitalWrite(dir1, HIGH);
        digitalWrite(dir2, LOW);
        analogWrite(enable, speed);
    }
    else if(speed < 0){
        digitalWrite(dir1, LOW);
        digitalWrite(dir2, HIGH);
        analogWrite(enable, 255-abs(speed));
    }
    else{
        digitalWrite(dir1, LOW);
        digitalWrite(dir2, LOW);
        digitalWrite(enable, LOW);
    }
}

void turn_off() {
  controlling = ! controlling; // Turn off control and motors
}

void control_vel() {
  float left_vel = cmdMessenger.readBinArg<float>(); // Left motors vel
  float right_vel = cmdMessenger.readBinArg<float>();  // Right motors vel
  //Aquí controla y lo hace todo

  // control motors
  control_motor(m1L_en,left_vel, mL_a,mL_b);
  control_motor(m2L_en,left_vel, mL_a,mL_b);
  control_motor(m3L_en,left_vel, mL_a,mL_b);

  control_motor(m1R_en,right_vel, mR_a,mR_b);
  control_motor(m2R_en,right_vel, mR_a,mR_b);
  control_motor(m3R_en,right_vel, mR_a,mR_b);
}

void shutdown_motors() { // Apagar los motores
  control_motor(m1L_en,0, mL_a,mL_b);
  control_motor(m2L_en,0, mL_a,mL_b);
  control_motor(m3L_en,0, mL_a,mL_b);

  control_motor(m1R_en,0, mR_a,mR_b);
  control_motor(m2R_en,0, mR_a,mR_b);
  control_motor(m3R_en,0, mR_a,mR_b);
}

// Callbacks define on which received commands we take action
void attachCommandCallbacks()
{
  cmdMessenger.attach(cmd_off, turn_off);
  cmdMessenger.attach(change_vel, control_vel);
}


void setup() {
  /* Motors pin init */
  pinMode(mL_a, OUTPUT); pinMode(mL_b, OUTPUT);

  pinMode(m1L_en, OUTPUT); pinMode(m1R_en, OUTPUT);
  pinMode(m2L_en, OUTPUT); pinMode(m2R_en, OUTPUT);
  pinMode(m3L_en, OUTPUT); pinMode(m3R_en, OUTPUT);

  // Listen on serial connection for messages from the PC
  // 115200 is the max speed on Arduino Uno
  Serial.begin(115200);

  // Adds newline to every command
  cmdMessenger.printLfCr();

  // Attach my application's user-defined callback methods
  attachCommandCallbacks();
}

/* Bucle infinito */
void loop() {

  if (controlling) cmdMessenger.feedinSerialData();  // Process incoming serial data, and perform callbacks
  else shutdown_motors();  // Stop controlling and power off motors: reset needed

  delay(1000);
}
