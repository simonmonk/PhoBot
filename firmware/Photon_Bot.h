#ifndef _Photon_Bot
#define _Photon_Bot
 
#include "application.h"
#include "SparkIntervalTimer/SparkIntervalTimer.h"
#include "SoftPWM/SoftPWM.h"
 
class PhotonBot
{
public: 
  PhotonBot();
  int setMotors(String command);
  void setMotor(int motor[], int direction);
  void setMotor(int motor[], int direction, float duty);
  int control(String command);
  float batteryVolts();
  void setStandby(boolean state);
  void setAutoStop(boolean state);
  
  int STOP = 0;
  int FORWARD = 1;
  int BACK = 2;
  
  int trigPin = D4;
  int echoPin = D5;
  
private:
  void init();
  void init(float batteryVoltage, float motorVoltage);
  
  float pwmFactor = 0.5;
  int standby = A3;
  int battery = A2;
  int M1[1] = {D7};
  int M2[1] = {D6};
  int M3[3] = {D3, A4, A5};
  int M4[3] = {D2, A1, A0};
};

 
#endif  
