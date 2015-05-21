#include "PhoBot.h"

 
PhoBot::PhoBot(){
    init();
}

PhoBot::PhoBot(float batteryVoltage, float motorVoltage){
    init(batteryVoltage, motorVoltage);
}

void PhoBot::init() {
    init(9.0, 6.0);
}

void PhoBot::init(float batteryVoltage, float motorVoltage) {
    pwmFactor = motorVoltage / batteryVoltage;
    if (pwmFactor > 1.0) {
        pwmFactor = 1.0;
    }
    pinMode(standby, OUTPUT);
    pinMode(M1[0], OUTPUT);
    pinMode(M2[0], OUTPUT);
    for (int i = 0; i < 3; i++) {
        pinMode(M3[i], OUTPUT);
        pinMode(M4[i], OUTPUT);
    }
    setStandby(false);
}

int PhoBot::control(String command) {
    // "F-100" - forward B, L, R
    String action = command.substring(0, 1);
    String speedStr = command.substring(2);
    float speed = 0;
    if (! action.equalsIgnoreCase("S")) {
        speed = speedStr.toInt() / 100.0;
    }
    if (action.equalsIgnoreCase("F")) {
        setMotor(M3, FORWARD, speed);
        setMotor(M4, FORWARD, speed);
    }
    else if (action.equalsIgnoreCase("B")) {
        setMotor(M3, BACK, speed);
        setMotor(M4, BACK, speed);
    }
    else if (action.equalsIgnoreCase("L")) {
        setMotor(M3, FORWARD, speed);
        setMotor(M4, BACK, speed);
    }
    else if (action.equalsIgnoreCase("R")) {
        setMotor(M3, BACK, speed);
        setMotor(M4, FORWARD, speed);
    }
    else if (action.equalsIgnoreCase("S")) {
        setMotor(M3, STOP);
        setMotor(M4, STOP);
    }
    return 1;
}


int PhoBot::setMotors(String command) {
    // "M3-F-100" use fixed positioning for first 2 params
    String motorName = command.substring(0, 2);
    String directionStr = command.substring(3, 4);
    String speedStr = command.substring(5);
    int direction = FORWARD;
    if (directionStr.equalsIgnoreCase("B")) {
        direction = BACK;
    }
    float speed = speedStr.toInt() / 100.0;
    if (motorName.equalsIgnoreCase("M3")) {
        setMotor(M3, direction, speed);
    }
    else if (motorName.equalsIgnoreCase("M4")) {
        setMotor(M4, direction, speed);
    }
    else if (motorName.equalsIgnoreCase("M1")) {
        setMotor(M1, FORWARD, speed);
    }
    else if (motorName.equalsIgnoreCase("M2")) {
        setMotor(M2, FORWARD, speed);
    }
    return 1;
}

void PhoBot::setMotor(int motor[], int direction) {
    setMotor(motor, direction, 1.0);
}

void PhoBot::setMotor(int motor[], int direction, float duty) {
    int pwm = int((duty * pwmFactor) * 256.0);
    if (pwm > 255) {
        pwm = 255;
    }
	if (motor == M1 || motor == M2) {
		digitalWrite(motor[0], pwm);
	}
    else if (motor == M3 || motor == M4) {
		analogWrite(motor[0], pwm);
        if (direction == STOP) {
            digitalWrite(motor[1], LOW);
            digitalWrite(motor[2], LOW);
        } 
        else if (direction == FORWARD) {
            digitalWrite(motor[1], LOW);
            digitalWrite(motor[2], HIGH);
        }
        else if (direction == BACK) {
            digitalWrite(motor[1], HIGH);
            digitalWrite(motor[2], LOW);
        }
    }
}

float PhoBot::batteryVolts() {
    int raw = analogRead(battery);
    float vout = raw * 3.3 / 4096.0;
    float k = 11.0; // ratio of R1 to R1+R2
    return vout * k + 0.33; // 0.3V forward voltage of D1
}

void PhoBot::setStandby(boolean state) {
    digitalWrite(standby, !state);
}
