
#include "acceleration.h"
#include "angle.h"
#include "ground.h"
#include "gravity.h"
#include "projectile.h"
#include "simulation_constants.h"
#include "velocity.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
   double angleDegrees = 0.0;

   cout << "What is the angle of the howitzer where 0 is up? ";
   string input;
   getline(cin, input);
   stringstream inputStream(input);
   if (!(inputStream >> angleDegrees))
      return 1;

   const Angle angle(angleDegrees);
   const Position start(0.0, 0.0);
   const Velocity initialVelocity = Velocity::fromSpeedAndAngle(
      SimulationConstants::DEFAULT_EXIT_VELOCITY_MPS, angle);
   const Gravity gravity(SimulationConstants::GRAVITY_MPS2);
   const Ground ground(0.0);

   Projectile projectile(start,
                         initialVelocity,
                         SimulationConstants::PROJECTILE_MASS_KG,
                         SimulationConstants::PROJECTILE_DIAMETER_M);
   Impact impact{ false, 0.0, start };

   while (!impact.occurred &&
          projectile.time() < SimulationConstants::MAX_SIMULATION_SECONDS)
   {
      impact = projectile.step(SimulationConstants::TIME_STEP_SECONDS,
                               gravity.acceleration(),
                               ground);
   }

   if (!impact.occurred)
      return 0;

   // Keep the un-interpolated altitude as a diagnostic log. The reported
   // distance and hang time use the interpolated ground-contact point.
   const double loggedAltitude = projectile.position().y();

   cout << fixed << setprecision(1)
        << "Distance: " << impact.position.x() << "m  "
        << "Altitude: " << loggedAltitude << "m  "
        << "Hang Time: " << impact.time << "s\n";
   return 0;
}
