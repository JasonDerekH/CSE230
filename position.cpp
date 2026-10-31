#include "position.h"
#include "velocity.h"
#include "acceleration.h"

void Position::advance(const Velocity& velocity,
                       const Acceleration& acceleration,
                       double dt)
{
   // abs() to account for negative angle input
   x_ += std::abs(velocity.dx() * dt + 0.5 * acceleration.ddx() * dt * dt);
   y_ += velocity.dy() * dt + 0.5 * acceleration.ddy() * dt * dt;
}
