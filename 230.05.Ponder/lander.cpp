/***********************************************************************
 * Source File:
 *    LANDER
 * Author:
 *    Br. Helfrich
 * Summary:
 *    All the information about the lunar lander
 ************************************************************************/

#include "lander.h"
#include "acceleration.h"

 /***************************************************************
  * RESET
  * Reset the lander and its position to start the game over
  ***************************************************************/
void Lander::reset(const Position& posUpperRight)
{
    // point straight up and start flying with a full tank
    angle.setRadians(0.0);
    status = PLAYING;
    fuel = 5000.0;

    // drifting left, with a little random up or down motion
    velocity.setDX(random(-10.0, -4.0));
    velocity.setDY(random(-2.0, 2.0));

    // start just inside the right edge, high on the screen
    pos.setX(posUpperRight.getX() - 1.0);
    pos.setY(random(posUpperRight.getY() * 0.75,
        posUpperRight.getY() * 0.95));
}

/***************************************************************
 * DRAW
 * Draw the lander on the screen
 ***************************************************************/
void Lander::draw(const Thrust& thrust, ogstream& gout) const
{
    // only show flames if we are flying and have fuel to burn
    if (isFlying() && fuel > 0.0)
        gout.drawLanderFlames(pos, angle.getRadians(),
            thrust.isMain(),
            thrust.isClock(),
            thrust.isCounter());

    gout.drawLander(pos, angle.getRadians());
}

/***************************************************************
 * INPUT
 * Accept input from the Neil Armstrong
 ***************************************************************/
Acceleration Lander::input(const Thrust& thrust, double gravity)
{
    // gravity always pulls down
    Acceleration acceleration;
    acceleration.addDDY(gravity);

    // no fuel means no engines
    if (fuel <= 0.0)
        return acceleration;

    // main engine pushes in the direction the lander is pointing
    if (thrust.isMain())
    {
        double power = thrust.mainEngineThrust();
        acceleration.addDDX(-sin(angle.getRadians()) * power);
        acceleration.addDDY(cos(angle.getRadians()) * power);
        fuel -= 10.0;
    }

    // side thrusters rotate the lander
    if (thrust.isClock() || thrust.isCounter())
    {
        angle.add(thrust.rotation());
        if (thrust.isClock())
            fuel -= 1.0;
        if (thrust.isCounter())
            fuel -= 1.0;
    }

    // don't let the tank go negative
    if (fuel < 0.0)
        fuel = 0.0;

    return acceleration;
}

/******************************************************************
 * COAST
 * What happens when we coast?
 *******************************************************************/
void Lander::coast(Acceleration& acceleration, double time)
{
    // move using the current velocity: s = s0 + vt + 1/2 at^2
    pos.setX(pos.getX()
        + velocity.getDX() * time
        + 0.5 * acceleration.getDDX() * time * time);
    pos.setY(pos.getY()
        + velocity.getDY() * time
        + 0.5 * acceleration.getDDY() * time * time);

    // then update the velocity: v = v0 + at
    velocity.setDX(velocity.getDX() + acceleration.getDDX() * time);
    velocity.setDY(velocity.getDY() + acceleration.getDDY() * time);
}