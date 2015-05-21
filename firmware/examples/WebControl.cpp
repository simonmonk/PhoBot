/*
curl https://api.spark.io/v1/devices/3b001b000447343232363230/setmotors -d access_token=172f237a43e4ed0ee25ddbb1507ebd5061bb19c5 -d params=M3-F-100
Commands are of the format: Motor-Direction-duty
Motor is one of:        M1, M2, M3, M4
Direction is one of:    F, B, S (forward, back, stop) - reverse has no effect on M1 and M2
Duty is percentage 0 to 100 and controls the motor speed.
M1 and M2 do not have PWM so duty is 0 or 1

To read the battery voltage use:
https://api.spark.io/v1/devices/3b001b000447343232363230/volts?access_token=172f237a43e4ed0ee25ddbb1507ebd5061bb19c5

To read the rangfinder distance in cm use:
https://api.spark.io/v1/devices/3b001b000447343232363230/distance?access_token=172f237a43e4ed0ee25ddbb1507ebd5061bb19c5



*/

#include "PhoBot/PhoBot.h"

double volts = 0.0;
double distance = 0.0;


PhoBot p = PhoBot();
HC_SR04 rangefinder = HC_SR04(p.trigPin, p.echoPin);

int control(String command) {
    return p.control(command);
}

int setMotors(String command) {
    return p.setMotors(command);
}

void setup() {
    Spark.function("control", control);
    Spark.function("setmotors", setMotors);
    Spark.variable("volts", &volts, DOUBLE);
    Spark.variable("distance", &distance, DOUBLE);
}

void loop() {
    volts = p.batteryVolts();
    distance = rangefinder.getDistanceCM();
    delay(100);
}
