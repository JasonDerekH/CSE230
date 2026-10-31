#include "position.h"
#include "velocity.h"
#include "acceleration.h"

void Position::advance(const Velocity& velocity,
                       const Acceleration& acceleration,
                       double dt)
{
   x_ += velocity.dx() * dt + 0.5 * acceleration.ddx() * dt * dt;
   y_ += velocity.dy() * dt + 0.5 * acceleration.ddy() * dt * dt;
}
