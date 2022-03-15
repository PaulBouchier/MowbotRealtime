#include <Arduino.h>
#include <SerialTransfer.h>
#include <MowbotMediator.h>
#include <PiLink.h>
#include <MowbotOdometry.h>
#include <RL500CommsTask.h>

HardwareSerial hardwareSerial1 = HardwareSerial(1);

// Define which serial port we'll use for PiLink
//#define LINK_SERIAL Serial
#define LINK_SERIAL hardwareSerial1

// Globals
PiLink piLink= PiLink( LINK_SERIAL ) ;
MowbotOdometry mowbotOdometry;
RL500CommsTask rl500CommsTask;
bool once = false;

// global messages that callers use to send or receive Pi messages
TxLog txLog = TxLog(piLink.piXfer_, piLink.linkLog_);
TxOdometry txOdometry = TxOdometry(piLink.piXfer_, piLink.linkLog_);
TxPong txPong = TxPong(piLink.piXfer_);
TxPlatformData txPlatformData = TxPlatformData(piLink.piXfer_, piLink.linkLog_);

RxBITMode rxBITMode = RxBITMode(piLink.piXfer_, piLink.linkLog_);
RxClearOdom rxClearOdom = RxClearOdom(piLink.piXfer_, piLink.linkLog_);
RxDriveMotorsRqst rxDriveMotorsRqst = RxDriveMotorsRqst(piLink.piXfer_);
RxLogLevel rxLogLevel = RxLogLevel(piLink.piXfer_, piLink.linkLog_);
RxPing rxPing = RxPing(piLink.piXfer_);
RxReboot rxReboot = RxReboot(piLink.piXfer_, piLink.linkLog_);

// Instantiate the mediator
MowbotMediator mowbotMediator(
                            mowbotOdometry,
                            rl500CommsTask,
                            piLink,
                            txLog,
                            txOdometry
                            );

// Stack pointer measurement support
void * StackPtrAtStart;
void * StackPtrEnd;
UBaseType_t watermarkStart;

void setup() {
  void* SpStart = NULL;
  StackPtrAtStart = (void *)&SpStart;
  watermarkStart =  uxTaskGetStackHighWaterMark(NULL);
  StackPtrEnd = StackPtrAtStart - watermarkStart;

  bool isok = true;

  Serial.begin(115200);
  delay(3000); // let serial start
  Serial.println("ESP32 setup() starting");

  // Uncomment to print stack info
  // Serial.printf("\r\n\r\nAddress of Stackpointer near start is:  %p \r\n",  (void *)StackPtrAtStart);
  // Serial.printf("End of Stack is near: %p \r\n",  (void *)StackPtrEnd);
  // Serial.printf("Free Stack near start is:  %d \r\n",  (uint32_t)StackPtrAtStart - (uint32_t)StackPtrEnd);

  // initialize odometry
  isok = mowbotOdometry.init(LOG_LEVEL_INFO);
  delay(1000);      // wait for startup messages from mowbotOdometry object to get printed

  // initialize RL500CommsTask
  isok = rl500CommsTask.init(LOG_LEVEL_INFO);
  delay(1000);    // wait for startup messages from rl500CommsTask to get printed
  if (isok)
    rl500CommsTask.rlCommsLog_.infoln("Successfully initialized rl500CommsTask and RL500");

  // initialize piLink
  isok = piLink.init(LOG_LEVEL_INFO);
  if (!isok)
  {
    Serial.println("piXfer init() failed");
  }

  piLink.linkLog_.infoln("Mowbot main() finished setup");
}

void loop() {
  delay(10000);
  if (!once)
  {
    // measure stack high water marks soon after startup
    void* SpActual = NULL;
    piLink.linkLog_.infoln("LoopTask free Stack after setup() is: %d", (uint32_t)&SpActual - (uint32_t)StackPtrEnd);
    piLink.linkLog_.infoln("piLink task stack free bytes: %d", piLink.getStackHighWaterMark());
    piLink.linkLog_.infoln("rl500Comms task stack free bytes: %d", rl500CommsTask.getStackHighWaterMark());
    piLink.linkLog_.infoln("mowbotOdometry task stack free bytes: %d", mowbotOdometry.getStackHighWaterMark());
    once = true;
  }
}