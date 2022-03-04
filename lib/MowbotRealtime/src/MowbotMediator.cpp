#include <MowbotMediator.h>

// globals
extern RxDriveMotorsRqst rxDriveMotorsRqst;
extern RxLogLevel rxLogLevel;
extern TxPlatformData txPlatformData;

MowbotMediator::MowbotMediator(
              MowbotOdometry& mobotOdometry,
              RL500CommsTask& rl500CommsTask,
              PiLink& piLink,
              TxLog& txLog,
              TxOdometry& txOdometry
              )
  : mowbotOdometry_(mobotOdometry)
  , rl500CommsTask_(rl500CommsTask)
  , piLink_(piLink)
  , txLog_(txLog)
  , txOdometry_(txOdometry)
{
  mowbotOdometry_.setMediator(this);
  rl500CommsTask_.setMediator(this);
  piLink_.setMediator(this);
  rxDriveMotorsRqst.setMediator(this);
  rxLogLevel.setMediator(this);
}

void
MowbotMediator::publishOdometry(OdometryMsg odom)
{
  if (odom.leftEncoderCount != lastLeftEncCnt_ || odom.rightEncoderCount != lastRightEncCnt_)
  {
    lastLeftEncCnt_ = odom.leftEncoderCount;
    lastRightEncCnt_ = odom.rightEncoderCount;
  }
  txOdometry_.post(odom);
}

void
MowbotMediator::setWheelDirections(bool leftFwd, bool rightFwd)
{
  mowbotOdometry_.setWheelDirections(leftFwd, rightFwd);
}

void
MowbotMediator::sendLogMsg(char* logMsg, int length)
{
  txLog_.post(logMsg, length);
}

void
MowbotMediator::setDrive(int32_t seq, float linear_vel, float angular_vel)
{
  piLink_.linkLog_.traceln("MowbotMediator got setDrive seq: %d left: %f right: %f", seq, linear_vel, angular_vel);
  rl500CommsTask_.setDrive(seq, linear_vel, angular_vel);
}

void
MowbotMediator::setLogLvl(int32_t pilinkLogLevel, int32_t rl500LogLevel, int32_t odomLogLevel)
{
  piLink_.linkLog_.setLevel(pilinkLogLevel);
  rl500CommsTask_.rlCommsLog_.setLevel(rl500LogLevel);
  mowbotOdometry_.odomLog_.setLevel(odomLogLevel);
}

void
MowbotMediator::publishPlatformData(PlatformDataMsg platformData)
{
  txPlatformData.post(platformData);
}