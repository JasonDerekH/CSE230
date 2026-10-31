#include "projectile.h"
#include "physics.h"
/*********************************************************
 * ACCELERATION
 * Gravity pulls straight down. Its strength depends on
 * the projectile's current altitude.
 *********************************************************/
Acceleration Projectile::acceleration() const
{
    const double altitude = position_.y();

    Acceleration total(0.0, -gravityFromAltitude(position_.y()));

    const double speed = velocity_.speed();
    if (speed > 0.0)
    {
        const double mach = speed / speedSoundFromAltitude(altitude);
        const double dragCoefficient = dragFromMach(mach);
        const double density = densityFromAltitude(altitude);

        const double force = forceFromDrag(density, dragCoefficient,
            diameterM_, speed);
        const double dragAccel = accelerationFromForce(force, massKg_);

        const Angle direction = Angle::fromRadians(
            std::atan2(velocity_.dx(), velocity_.dy()));

        const Angle opposite = Angle::fromRadians(
            direction.radians() + Angle(180.0).radians());

        total.add(Acceleration::fromMagnitudeAndAngle(dragAccel, opposite));
    }

    return total;
}
/*********************************************************
 * STEP
 * Advance one time unit: position first (distance formula),
 * then velocity (kinematics). If we went through the ground,
 * interpolate back to the exact moment of impact.
 *********************************************************/
Impact Projectile::step(double dt,
                        const Ground& ground)
{
   const Acceleration acceleration = this->acceleration();
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
