#pragma once

#include "position.h"

class Ground
{
public:
   explicit Ground(double elevation = 0.0) : elevation_(elevation) {}

   double elevationAt(double /*x*/) const { return elevation_; }
   bool isBelow(const Position& position) const;

   // Returns the fraction of the last timestep at which the path reached ground.
   double impactFraction(const Position& previous, const Position& current) const;

private:
   double elevation_;
};
