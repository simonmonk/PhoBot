/* 

This is an example program for the Photon_Bot library for the
Robot controller of the same name, by MonkMakes.com

You will need to include the following public libraries:

HC_SR04
SoftPWM
SparkIntervalTimer

*/

#include "PhoBot/PhoBot.h"


double volts = 0.0;
double distance = 0.0;


PhoBot p = PhoBot();
HC_SR04 rangefinder = HC_SR04(p.trigPin, p.echoPin);

void setup() {
    Spark.function("control", control);
    Spark.variable("volts", &volts, DOUBLE);
    Spark.variable("distance", &distance, DOUBLE);
}

void loop() {
    volts = p.batteryVolts();
    distance = rangefinder.getDistanceCM();
}

int control(String command) {
    return p.control(command);
}
