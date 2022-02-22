#include <Arduino.h>
#include <SerialTransfer.h>
#include <MowbotMediator.h>
#include <PiLink.h>
#include <MowbotOdometry.h>
#include <RL500CommsTask.h>

// Define which serial port we'll use for PiLink
//#define LINK_SERIAL Serial
HardwareSerial hardwareSerial1 = HardwareSerial(1);
#define LINK_SERIAL hardwareSerial1

// Globals
PiLink piLink= PiLink( LINK_SERIAL ) ;
MowbotOdometry mowbotOdometry;
RL500CommsTask rl500CommsTask;

// global messages that callers use to send or receive Pi messages
TxPong txPong = TxPong(piLink.piXfer_);
TxLog txLog = TxLog(piLink.piXfer_);
TxOdometry txOdometry = TxOdometry(piLink.piXfer_);

RxDriveMotorsRqst rxDriveMotorsRqst = RxDriveMotorsRqst(piLink.piXfer_);
RxPing rxPing = RxPing(piLink.piXfer_);

// Instantiate the mediator
MowbotMediator mowbotMediator(
                            mowbotOdometry,
                            rl500CommsTask,
                            piLink,
                            txLog,
                            txOdometry,
                            rxDriveMotorsRqst
                            );

void setup() {
  bool isok = true;

  Serial.begin(115200);
  delay(3000); // let serial start

  // initialize odometry
  isok = mowbotOdometry.init(LOG_LEVEL_VERBOSE);
  delay(1000);      // wait for startup messages from mowbotOdometry object to get printed

  // initialize RL500CommsTask
  isok = rl500CommsTask.init(LOG_LEVEL_VERBOSE);
  delay(1000);    // wait for startup messages from rl500CommsTask to get printed
  if (isok)
    rl500CommsTask.rlCommsLog_.infoln("Successfully initialized rl500CommsTask and RL500");

  // initialize piLink
  isok = piLink.init(LOG_LEVEL_VERBOSE);
  if (!isok)
  {
    Serial.println("piXfer init() failed");
  }

  piLink.linkLog_.infoln("Mowbot main() finished setup");
}

void loop() {
  piLink.linkLog_.infoln("MowbotRealtime in loop()");
  delay(2000);
}