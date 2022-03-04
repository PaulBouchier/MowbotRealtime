#pragma once

struct OdometryMsg {
  int32_t seq;
  TickType_t espTimestamp;
  float poseX_m;
  float poseY_m;
  float heading_rad;
  float speedX_mps;
  float speedY_mps;
  float linear_speed_mps;
  float angular_speed_rps;
  float odometer_m;
  float leftSpeed;
  float rightSpeed;

  int leftEncoderCount;
  int rightEncoderCount;
  float leftWheelAngle_rad;
  float rightWheelAngle_rad;
};
