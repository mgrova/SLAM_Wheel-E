#include <Arduino.h>
#include <string.h>

/*
ENABLE |      PWM     |     DIG      |   STATUS           |
--------------------------------------------------------- |
LOW    |    ----      |    ----      |MOTOR PARADO        |
HIGH   |    HIGH      |     LOW      |MOTOR GIRA DELANTE  |
HIGH   |    LOW       |     HIGH     |MOTOR GIRA AL REVES |
HIGH   |    HIGH      |     HIGH     |MOTOR PARADO        |
HIGH   |    LOW       |     LOW      |MOTOR PARADO        |
 */

/* Define the pin numbers */
#define m1L_pwm 3
#define m1L_dig 27
#define m2L_pwm 5
#define m2L_dig 29
#define m3L_pwm 7
#define m3L_dig 31

#define m1R_pwm 2
#define m1R_dig 26
#define m2R_pwm 4
#define m2R_dig 28
#define m3R_pwm 6
#define m3R_dig 30 

#define enable_pH 14

void setup() {
    Serial.begin(115200);

    pinMode(m1L_pwm, OUTPUT); pinMode(m1L_dig, OUTPUT);
    pinMode(m2L_pwm, OUTPUT); pinMode(m2L_dig, OUTPUT);
    pinMode(m3L_pwm, OUTPUT); pinMode(m3L_dig, OUTPUT);

    pinMode(m1R_pwm, OUTPUT); pinMode(m1R_dig, OUTPUT);
    pinMode(m2R_pwm, OUTPUT); pinMode(m2R_dig, OUTPUT);
    pinMode(m3R_pwm, OUTPUT); pinMode(m3R_dig, OUTPUT);
}


/* function to control motor */
void control_motor(int enable,int speed, int pwmPin, int DigPin){
    if(speed > 0){
        if (speed>125) speed=125;
        digitalWrite(enable, HIGH);
        analogWrite(pwmPin, speed);
        digitalWrite(DigPin, LOW);
    }
    else if(speed < 0){
        speed=-speed;
        if (speed>125) speed=125;
        digitalWrite(enable, HIGH);
        analogWrite(pwmPin, speed);
        digitalWrite(DigPin, HIGH);
    }
    else{
        digitalWrite(enable, LOW);
        digitalWrite(DigPin, LOW);
    }
}

/* Bucle infinito */
void loop() {

    static int speed[6];
    static char buff[30];
    int counter = 0;
    // read command from raspberry pi
    while(Serial.available()){
        buff[counter] = Serial.read();
        if (counter > 30 || buff[counter] == '*') {
            buff[counter] = '\0';
            speed[0]=atoi(strtok(buff,","));
            speed[1]=atoi(strtok(NULL,","));
            speed[2]=atoi(strtok(NULL,","));
            speed[3]=atoi(strtok(NULL,","));
            speed[4]=atoi(strtok(NULL,","));
            speed[5]=atoi(strtok(NULL,","));
        }
        else{
            counter++;
        }
    }

    // control motors
    control_motor(enable_pH,speed[0], m1L_pwm,m1L_dig);
    control_motor(enable_pH,speed[1], m2L_pwm,m2L_dig);
    control_motor(enable_pH,speed[2], m3L_pwm,m3L_dig);

    control_motor(enable_pH,speed[3], m1R_pwm,m1R_dig);
    control_motor(enable_pH,speed[4], m2R_pwm,m2R_dig);
    control_motor(enable_pH,speed[5], m3R_pwm,m3R_dig);

    // send messages to raspberry pi
    Serial.print(speed[0]); Serial.print(",");
    Serial.print(speed[1]); Serial.print(",");
    Serial.print(speed[2]); Serial.print(",");
    Serial.print(speed[3]); Serial.print(",");
    Serial.print(speed[4]); Serial.print(",");
    Serial.println(speed[5]);

    delay(100);
}
