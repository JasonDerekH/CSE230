#pragma once

#include "angle.h"

class Acceleration;

class Velocity
{
public:
   Velocity() : dx_(0.0), dy_(0.0) {}
   Velocity(double dx, double dy) : dx_(dx), dy_(dy) {}

   static Velocity fromSpeedAndAngle(double speed, const Angle& angle);

   double dx() const { return dx_; }
   double dy() const { return dy_; }
   double speed() const;

   void add(const Acceleration& acceleration, double dt);

private:
   double dx_;
   double dy_;
};
