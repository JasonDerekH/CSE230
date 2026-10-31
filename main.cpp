/*************************************************************
 * 1. Name:
 *      Riley Cluff and Jason Hollingsworth
 * 2. Assignment Name:
 *      Lab 07: Artillery Prototype
 * 3. Assignment Description:
 *      Compute how far an M795 projectile travels and how long
 *      it is in the air when fired from an M777 howitzer
**************************************************************/

#include "angle.h"
#include "ground.h"
#include "position.h"
#include "projectile.h"
#include "simulation_constants.h"
#include "velocity.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

/*************************************************************
 * MAIN
 * Ask for the angle, fire the projectile, and step it forward
 * until it hits the ground
 **************************************************************/
int main()
{
    double angleDegrees = 0.0;

    cout << "What is the angle of the howitzer where 0 is up? ";
    string input;
    getline(cin, input);
    stringstream inputStream(input);
    if (!(inputStream >> angleDegrees))
    {
        cout << "Invalid angle\n";
        return 1;
    }

    const Angle angle(angleDegrees);
    const Position start(0.0, 0.0);
    const Velocity initialVelocity = Velocity::fromSpeedAndAngle(
        SimulationConstants::DEFAULT_EXIT_VELOCITY_MPS, angle);
    const Ground ground(0.0);

    Projectile projectile(start,
        initialVelocity,
        SimulationConstants::PROJECTILE_MASS_KG,
        SimulationConstants::PROJECTILE_DIAMETER_M);
    Impact impact{ false, 0.0, start };

    while (!impact.occurred &&
        projectile.time() < SimulationConstants::MAX_SIMULATION_SECONDS)
        impact = projectile.step(SimulationConstants::TIME_STEP_SECONDS, ground);

    if (!impact.occurred)
    {
        cout << "The projectile never hit the ground\n";
        return 0;
    }

    cout << fixed << setprecision(1)
        << "Distance: " << setw(12) << impact.position.x() << "m       "
        << "Hang Time: " << setw(10) << impact.time << "s\n";
    return 0;
}