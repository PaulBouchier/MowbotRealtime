#pragma once

#include <Arduino.h>

struct PlatformDataMsg {
  int seq;              // sequence #
  TickType_t espTimestamp; // time data was recorded on esp
  float leftMps;        // requested left speed m/s
  float rightMps;       // requested right speed m/s
  int32_t leftPct;      // requested left percent power
  int32_t rightPct;     // requested right percent power
};