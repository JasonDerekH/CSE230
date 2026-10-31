#pragma once

#include <cmath>

class Angle
{
public:
   Angle() : radians_(0.0) {}
   explicit Angle(double degrees) : radians_(degrees * PI / 180.0) {}

   static Angle fromRadians(double radians)
   {
      Angle angle;
      angle.radians_ = radians;
      return angle;
   }

   double radians() const { return radians_; }
   double degrees() const { return radians_ * 180.0 / PI; }

private:
   static constexpr double PI = 3.14159265358979323846;
   double radians_;
};
