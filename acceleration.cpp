#include "acceleration.h"

#include <cmath>

Acceleration Acceleration::fromMagnitudeAndAngle(double magnitude, const Angle& angle)
{
   return Acceleration(magnitude * std::sin(angle.radians()),
                       magnitude * std::cos(angle.radians()));
}

void Acceleration::add(const Acceleration& other)
{
   ddx_ += other.ddx_;
   ddy_ += other.ddy_;
}
