#include "projectile.h"

Impact Projectile::step(double dt,
                        const Acceleration& acceleration,
                        const Ground& ground)
{
   const Position previous = position_;
   position_.advance(velocity_, acceleration, dt);
   velocity_.add(acceleration, dt);
   time_ += dt;

   if (!ground.isBelow(position_))
      return { false, time_, position_ };

   const double fraction = ground.impactFraction(previous, position_);
   Position impact(previous.x() + fraction * (position_.x() - previous.x()),
                   previous.y() + fraction * (position_.y() - previous.y()));
   return { true, time_ - dt + fraction * dt, impact };
}
