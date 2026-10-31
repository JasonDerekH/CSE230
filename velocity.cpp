#include "velocity.h"
#include "acceleration.h"

#include <cmath>

Velocity Velocity::fromSpeedAndAngle(double speed, const Angle& angle)
{
   // The simulator uses 0 degrees as straight up.
   return Velocity(speed * std::sin(angle.radians()),
                  speed * std::cos(angle.radians()));
}

double Velocity::speed() const
{
   return std::sqrt(dx_ * dx_ + dy_ * dy_);
}

void Velocity::add(const Acceleration& acceleration, double dt)
{
   dx_ += acceleration.ddx() * dt;
   dy_ += acceleration.ddy() * dt;
}
