#pragma once

#include "acceleration.h"

class Gravity
{
public:
   explicit Gravity(double magnitude = 9.80665) : acceleration_(0.0, -magnitude) {}

   Acceleration acceleration() const { return acceleration_; }
   void setMagnitude(double magnitude) { acceleration_ = Acceleration(0.0, -magnitude); }

private:
   Acceleration acceleration_;
};
