#pragma once

#include <Arduino.h>
#include <OdometryMsg.h>

class Mediator
{
public:
  virtual void setWheelDirections(bool leftFwd, bool rightFwd) = 0;
  virtual void sendLogMsg(char* logMsg, int length) = 0;
  virtual void setDrive(int8_t leftDrivePct, int8_t rightDrivePct) = 0;
  virtual void publishOdometry(OdometryMsg odom) = 0;
};
