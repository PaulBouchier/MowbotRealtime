#pragma once

#include <Mediator.h>
#include <ArduinoLog.h>
#include <MowbotOdometry.h>
#include <RL500CommsTask.h>
#include <PiLink.h>

class MowbotOdometry;
class RL500CommsTask;
class PiLink;

class MowbotMediator : public Mediator
{
public:
  MowbotMediator(
                MowbotOdometry& mobotOdometry,
                RL500CommsTask& rl500CommsTask,
                PiLink& piLink,
                TxLog& txLog,
                TxOdometry& txOdometry
                );
  void setWheelDirections(bool leftFwd, bool rightFwd);
  void sendLogMsg(char* logMsg, int length);
  void setDrive(int32_t seq, float linear_vel, float angular_vel);
  void publishOdometry(OdometryMsg odom);
  void clearOdometry();
  void setLogLvl(int32_t pilinkLogLevel, int32_t rl500LogLevel, int32_t odomLogLevel);
  void publishPlatformData(PlatformDataMsg platformData);
  void setRL500BITMode();

private:
  MowbotOdometry& mowbotOdometry_;
  RL500CommsTask& rl500CommsTask_;
  PiLink& piLink_;
  TxLog& txLog_;
  TxOdometry& txOdometry_;

  // OdomMediator variables
  int lastLeftEncCnt_ = 0;       // last received encoder count
  int lastRightEncCnt_ = 0;      // last received encoder count

};