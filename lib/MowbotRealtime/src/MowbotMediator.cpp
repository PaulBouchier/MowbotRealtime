#include <MowbotMediator.h>

MowbotMediator::MowbotMediator(
              MowbotOdometry& mobotOdometry,
              RL500CommsTask& rl500CommsTask,
              PiLink& piLink,
              TxLog& txLog,
              TxOdometry& txOdometry,
              RxDriveMotorsRqst& rxDriveMotorsRqst
              )
  : mowbotOdometry_(mobotOdometry)
  , rl500CommsTask_(rl500CommsTask)
  , piLink_(piLink)
  , txLog_(txLog)
  , txOdometry_(txOdometry)
  , rxDriveMotorsRqst_(rxDriveMotorsRqst)
{
  mowbotOdometry_.setMediator(this);
  rl500CommsTask_.setMediator(this);
  piLink_.setMediator(this);
  rxDriveMotorsRqst.setMediator(this);
}

void
MowbotMediator::publishOdometry(OdometryMsg odom)
{

  if (odom.leftEncoderCount != lastLeftEncCnt_ || odom.rightEncoderCount != lastRightEncCnt_)
  {
    char odomMsg[200];
    snprintf(odomMsg, 200, "EncoderMediator saw poseX: %0.2f m, poseY: %0.2f m, heading: %0.0f deg, left speed: %0.2f m/s, right speed: %0.2f m/s",
            odom.poseX_m, odom.poseY_m, odom.heading_rad * (180 / M_PI), odom.leftSpeed, odom.rightSpeed);
    mowbotOdometry_.odomLog_.verboseln(odomMsg);
    lastLeftEncCnt_ = odom.leftEncoderCount;
    lastRightEncCnt_ = odom.rightEncoderCount;
  }
  txOdometry_.post(odom);
}

void
MowbotMediator::setWheelDirections(bool leftFwd, bool rightFwd)
{
  rl500CommsTask_.rlCommsLog_.infoln("RL500Mediator saw direction change, new left: %T, right %T", leftFwd, rightFwd);
}

void
MowbotMediator::sendLogMsg(char* logMsg, int length)
{
  txLog_.post(logMsg, length);
}

void
MowbotMediator::setDrive(int8_t leftDrivePct, int8_t rightDrivePct)
{
  delay(200);
  piLink_.linkLog_.traceln("MowbotMediator got setDrive left: %d right: %d", leftDrivePct, rightDrivePct);
  rl500CommsTask_.setDrive(leftDrivePct, rightDrivePct);
}
