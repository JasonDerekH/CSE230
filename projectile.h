#pragma once

#include "acceleration.h"
#include "ground.h"
#include "position.h"
#include "velocity.h"

struct Impact
{
   bool occurred;
   double time;
   Position position;
};

class Projectile
{
public:
   Projectile(const Position& position,
              const Velocity& velocity,
              double massKg,
              double diameterM)
      : position_(position), velocity_(velocity), massKg_(massKg),
        diameterM_(diameterM), time_(0.0) {}

   const Position& position() const { return position_; }
   const Velocity& velocity() const { return velocity_; }
   double massKg() const { return massKg_; }
   double diameterM() const { return diameterM_; }
   double time() const { return time_; }

   // Inertia: velocity is retained unless an acceleration changes it.
   Impact step(double dt, const Ground& ground);

private:
   Acceleration acceleration() const;

   Position position_;
   Velocity velocity_;
   double massKg_;
   double diameterM_;
   double time_;
};
