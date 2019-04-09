#include <CmdMessenger.h>

bool controlling = 1; // 1 if control active & motors can run

// Attach a new CmdMessenger object to the default Serial port
CmdMessenger cmdMessenger = CmdMessenger(Serial);

enum {
  cmd_off,  // Cmd to deactivate control & motors. Reset needed after this
  cmd_vel,      // Cmd to change velocities, with left motors vel and right motors vel as arguments (float32)
};

// Callbacks define on which received commands we take action 
void attachCommandCallbacks()
{
  cmdMessenger.attach(cmd_off, turn_off);
  cmdMessenger.attach(cmd_vel, control_vel);
}

void turn_off() {
  controlling = ! controlling; // Turn off control and motors
}

void control_vel() {
  float left_vel = cmdMessenger.readFloatArg(); // Left motors vel
  float right_vel = cmdMessenger.readFloatArg();  // Right motors vel
  //Aquí controla y lo hace todo
  
}

void shutdown_motors() {
  // Apagar los motores
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

}

void loop() {
  if controlling
    cmdMessenger.feedinSerialData();  // Process incoming serial data, and perform callbacks
  else
    shutdown_motors();  // Stop controlling and power off motors
}
