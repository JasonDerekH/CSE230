#pragma once

#include "angle.h"

class Acceleration
{
public:
   Acceleration() : ddx_(0.0), ddy_(0.0) {}
   Acceleration(double ddx, double ddy) : ddx_(ddx), ddy_(ddy) {}

   static Acceleration fromMagnitudeAndAngle(double magnitude, const Angle& angle);

   double ddx() const { return ddx_; }
   double ddy() const { return ddy_; }
   void add(const Acceleration& other);

private:
   double ddx_;
   double ddy_;
};
