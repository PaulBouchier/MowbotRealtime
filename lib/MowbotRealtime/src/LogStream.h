#pragma once

#include <Arduino.h>
#include <Mediator.h>


// @brief class that implements a stream-like class for use by Arduino logs
class LogStream : public Stream
{
public:
  LogStream();
  size_t write(uint8_t);            // implements pure virtual method from Print
  int available() {return 0; };     // implements pure virtual method from Stream
  int read() {return 0; }           // implements pure virtual method from Stream
  int peek()  {return 0; }          // implements pure virtual method from Stream
  void flush() {};                  // implements pure virtual method from Stream
  void setMediator(Mediator* mediator) { mediator_ = mediator; }

private:
  const int bufSize = 128;          // size of logging buffer instantiated in LogStream objects

  char *buff_;                      // buffer for storing logs
  char *buffp_;                     // pointer to current write location
  int logLength_;                   // number of bytes in buffer

  Mediator* mediator_ = NULL;
};