#include "PhoBot/PhoBot.h"

PhoBot p = PhoBot(9.0, 6.0);

void setup() {
    pinMode(A3, OUTPUT);
    pinMode(A4, OUTPUT);
    pinMode(A5, OUTPUT);
}

void loop() {
    pause();
    p.setMotors("M1-F-100");
    p.setMotors("M2-F-100");
    delay(2000);
    pause();
    p.setMotors("M1-F-50");
    p.setMotors("M2-F-50");
    delay(2000);
    p.setMotors("M1-S");
    p.setMotors("M2-S");

    pause();
    p.setMotors("M3-F-100");
    p.setMotors("M4-F-100");
    digitalWrite(A3, HIGH);
    delay(2000);
    pause();
    p.setMotors("M3-B-100");
    p.setMotors("M4-B-100");
    digitalWrite(A3, HIGH);
    delay(2000);
    pause();
    p.setMotors("M3-F-50");
    p.setMotors("M4-F-50");
    digitalWrite(A3, HIGH);
    delay(2000);
}

void pause() {
    p.setMotors("M3-S");
    p.setMotors("M4-S");
    digitalWrite(A3, LOW);
    delay(100);
}
