#include <Arduino.h>
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
#define m3L_a 31
#define m3L_b 30
#define m3L_en 2

#define m2L_a 29
#define m2L_b 28
#define m2L_en 3

#define m1L_a 27
#define m1L_b 26
#define m1L_en 4

#define m3R_a 25
#define m3R_b 24
#define m3R_en 5

#define m2R_a 23
#define m2R_b 22
#define m2R_en 6

#define m1R_a 21
#define m1R_b 20
#define m1R_en 7

void setup() {
    Serial.begin(115200);

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


/* function to control motor */
void control_motor(int enable,int speed, int dir1, int dir2){
    if(speed > 0){
        if (speed>125) speed=125;
        digitalWrite(dir1, HIGH);
        digitalWrite(dir2, LOW);
        analogWrite(enable, speed);
    }
    else if(speed < 0){
        speed=-speed;
        if (speed>125) speed=125;
        digitalWrite(dir1, LOW);
        digitalWrite(dir2, HIGH);
        analogWrite(enable, speed);
    }
    else{
        digitalWrite(dir1, LOW);
        digitalWrite(dir2, LOW);
        digitalWrite(enable, LOW);
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
    control_motor(m1L_en,speed[0], m1L_a,m1L_b);
    control_motor(m2L_en,speed[1], m2L_a,m2L_b);
    control_motor(m3L_en,speed[2], m3L_a,m3L_b);

    control_motor(m1R_en,speed[3], m1R_a,m1R_b);
    control_motor(m2R_en,speed[4], m2R_a,m2R_b);
    control_motor(m3R_en,speed[5], m3R_a,m3R_b);

    // send messages to raspberry pi
    Serial.print(speed[0]); Serial.print(",");
    Serial.print(speed[1]); Serial.print(",");
    Serial.print(speed[2]); Serial.print(",");
    Serial.print(speed[3]); Serial.print(",");
    Serial.print(speed[4]); Serial.print(",");
    Serial.println(speed[5]);

    delay(100);
}
