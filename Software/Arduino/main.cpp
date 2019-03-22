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
#define m3L_a 35
#define m3L_b 34
#define m3L_en 2

#define m2L_a 39
#define m2L_b 38
#define m2L_en 3

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

void setup() {

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

    static int speed[6]={120,120,120,120,120,120};
    static char buff[30];
    int counter = 0;


    // control motors
    control_motor(m1L_en,speed[0], m1L_a,m1L_b);
    control_motor(m1R_en,speed[0], m1R_a,m1R_b);
    control_motor(m2L_en,speed[0], m2L_a,m2L_b);
    control_motor(m2R_en,speed[0], m2R_a,m2R_b);
    control_motor(m3L_en,speed[0], m3L_a,m3L_b);
    control_motor(m3R_en,speed[0], m3R_a,m3R_b);


    delay(100);
}
