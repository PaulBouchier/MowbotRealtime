#pragma once

#include <Arduino.h>

struct PlatformDataMsg {
  int seq;              // sequence #
  TickType_t espTimestamp; // time data was recorded on esp
  float leftMps;        // requested left speed m/s
  float rightMps;       // requested right speed m/s
  int32_t leftPct;      // requested left percent power
  int32_t rightPct;     // requested right percent power
  float commandedLinear;  // last commanded linear speed
  float commandedAngular; // last commanded angular speed
  int32_t bumperPressed;  // true if any bumpers are pressed
};