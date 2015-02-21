double volts = 0.0;
double distance = 0.0;


PhotonBot p = PhotonBot();
HC_SR04 rangefinder = HC_SR04(p.trigPin, p.echoPin);

int control(String command) {
    return p.control(command);
}

int setMotors(String command) {
    return p.setMotors(command);
}

void setup() {
    SoftPWMBegin();
    Spark.function("control", control);
    Spark.function("setmotors", setMotors);
    Spark.variable("volts", &volts, DOUBLE);
    Spark.variable("distance", &distance, DOUBLE);
}

void loop() {
    volts = p.batteryVolts();
    distance = rangefinder.getDistanceCM();
}
