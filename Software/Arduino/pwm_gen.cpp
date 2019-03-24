#include <Arduino.h>
#include <CmdMessenger.h> // https://github.com/thijse/Arduino-CmdMessenger
#include <string.h>

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
#define m3L_a 39//35
#define m3L_b 38//34
#define m3L_en 3//2

#define m2L_a 35//39
#define m2L_b 34//38
#define m2L_en 2//3

#define m1L_a 43
#define m1L_b 42
#define m1L_en 4

#define m3R_a 32
#define m3R_b 33
#define m3R_en 5

#define m2R_a 36
#define m2R_b 37
#define m2R_en 6

#define m1R_a 40
#define m1R_b 41
#define m1R_en 7

// Attach a new CmdMessenger object to the default Serial port
CmdMessenger cmdMessenger = CmdMessenger(Serial);

// We can define up to a default of 50 cmds total, including both directions (send + receive)
// and including also the first 4 default command codes for the generic error handling.
// If you run out of message slots, then just increase the value of MAXCALLBACKS in CmdMessenger.h

 // This is the list of recognized commands. These can be commands that can either be sent or received.
 // In order to receive, attach a callback function to these events
 //
 // Note that commands work both directions:
 // - All commands can be sent
 // - Commands that have callbacks attached can be received
 //
 // This means that both sides should have an identical command list:
 // both sides can either send it or receive it (or even both)

// Commands
enum
{
  data, // Command to request led to be set in specific state

};

// Callbacks define on which received commands we take action
void attachCommandCallbacks()
{
  cmdMessenger.attach(data, reading);
}

void reading() {
  vector6 = cmdMessenger.read...
  digitalWrite(m1L_a, vector[6])
}

void setup() {
  // Listen on serial connection for messages from the PC
  // 115200 is the max speed on Arduino Uno, Mega, with AT8u2 USB
  // Use 57600 for the Arduino Duemilanove and others with FTDI Serial
  Serial.begin(115200);

  // Adds newline to every command
  cmdMessenger.printLfCr();

  // Attach my application's user-defined callback methods
  attachCommandCallbacks();

  //pins:
    pinMode(m1L_a, OUTPUT); pinMode(m1L_b, OUTPUT);
    pinMode(m2L_a, OUTPUT); pinMode(m2L_b, OUTPUT);
    pinMode(m3L_a, OUTPUT); pinMode(m3L_b, OUTPUT);

    pinMode(m1R_a, OUTPUT); pinMode(m1R_b, OUTPUT);
    pinMode(m2R_a, OUTPUT); pinMode(m2R_b, OUTPUT);
    pinMode(m3R_a, OUTPUT); pinMode(m3R_b, OUTPUT);

    pinMode(m1L_en, OUTPUT); pinMode(m1R_en, OUTPUT);
    pinMode(m2L_en, OUTPUT); pinMode(m2R_en, OUTPUT);
    pinMode(m3L_en, OUTPUT); pinMode(m3R_en, OUTPUT);
}

void loop()
{
  // Process incoming serial data, and perform callbacks
  cmdMessenger.feedinSerialData();
}
