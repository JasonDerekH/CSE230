#include "ground.h"

bool Ground::isBelow(const Position& position) const
{
   return position.y() <= elevationAt(position.x());
}

double Ground::impactFraction(const Position& previous, const Position& current) const
{
   const double previousHeight = previous.y() - elevationAt(previous.x());
   const double currentHeight = current.y() - elevationAt(current.x());
   const double denominator = previousHeight - currentHeight;

   if (denominator == 0.0)
      return 1.0;

   const double fraction = previousHeight / denominator;
   return fraction < 0.0 ? 0.0 : (fraction > 1.0 ? 1.0 : fraction);
}
