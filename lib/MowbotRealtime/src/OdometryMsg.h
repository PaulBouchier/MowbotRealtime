#pragma once

struct OdometryMsg {
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
};
