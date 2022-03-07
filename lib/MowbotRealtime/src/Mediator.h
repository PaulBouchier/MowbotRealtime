#pragma once

#include <Arduino.h>
#include <OdometryMsg.h>
#include <PlatformDataMsg.h>

class Mediator
{
public:
  virtual void setWheelDirections(bool leftFwd, bool rightFwd) = 0;
  virtual void sendLogMsg(char* logMsg, int length) = 0;
  virtual void setDrive(int32_t seq, float linear_vel, float angular_vel) = 0;
  virtual void publishOdometry(OdometryMsg odom) = 0;
  virtual void setLogLvl(int32_t pilinkLogLevel, int32_t rl500LogLevel, int32_t odomLogLevel) = 0;
  virtual void publishPlatformData(PlatformDataMsg platformData) = 0;
  virtual void setRL500BITMode() = 0;
};
