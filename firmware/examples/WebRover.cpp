/* 

This is an example program for the Photon_Bot library for the
Robot controller of the same name, by MonkMakes.com

You will need to include the HC_SR04 library

*/

#include "PhoBot/PhoBot.h"


double volts = 0.0;
double distance = 0.0;


PhoBot p = PhoBot(6.0, 3.0); //assuming you are using ABRA kit.
HC_SR04 rangefinder = HC_SR04(p.trigPin, p.echoPin);

void setup() {
    Spark.function("control", control);
    Spark.variable("volts", &volts, DOUBLE);
    Spark.variable("distance", &distance, DOUBLE);
    pinMode(A3, OUTPUT);
    pinMode(A4, OUTPUT);
    pinMode(A5, OUTPUT);
}

void loop() {
    volts = p.batteryVolts();
    distance = rangefinder.getDistanceCM();
}

int control(String command) {
    if(command == "M3-S" || command == "M4-S")
    {
        p.setMotors(command);
        digitalWrite(A3, LOW);
    }
    else
    {
        p.setMotors(command);
        digitalWrite(A3, HIGH);
    }
    p.setMotors(command);
    return p.control(command);
}
