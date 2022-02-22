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
                TxOdometry& txOdometry,
                RxDriveMotorsRqst& rxDriveMotorsRqst
                );
  void setWheelDirections(bool leftFwd, bool rightFwd);
  void sendLogMsg(char* logMsg, int length);
  void setDrive(int8_t leftDrivePct, int8_t rightDrivePct);
  void publishOdometry(OdometryMsg odom);

private:
  MowbotOdometry& mowbotOdometry_;
  RL500CommsTask& rl500CommsTask_;
  PiLink& piLink_;
  TxLog& txLog_;
  TxOdometry& txOdometry_;
  RxDriveMotorsRqst& rxDriveMotorsRqst_;

  // OdomMediator variables
  int lastLeftEncCnt_ = 0;       // last received encoder count
  int lastRightEncCnt_ = 0;      // last received encoder count

};