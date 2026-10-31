/***********************************************************************
 * Source File:
 *    VELOCITY
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about speed
 ************************************************************************/

#include "velocity.h"
#include "acceleration.h"
#include "angle.h"

#include <math.h>  // for sqrt(), sin(), and cos()

 /*********************************************
  * VELOCITY : ADD
  *  v = v_0 + a t
  *  Apply an acceleration over a period of time.
  *********************************************/
void Velocity::add(const Acceleration& acceleration, double time)
{
	dx += acceleration.getDDX() * time;
	dy += acceleration.getDDY() * time;
}

/*********************************************
 * VELOCITY : GET SPEED
 *  Find the magnitude of velocity using the
 *  Pythagorean theorem.
 *********************************************/
double Velocity::getSpeed() const
{
	return sqrt(dx * dx + dy * dy);
}

/*********************************************
 * VELOCITY : SET
 *  Set from angle and magnitude. An angle of 0
 *  points straight up, so sin() gives the
 *  horizontal part and cos() gives the vertical.
 *********************************************/
void Velocity::set(const Angle& angle, double magnitude)
{
	dx = magnitude * sin(angle.getRadians());
	dy = magnitude * cos(angle.getRadians());
}