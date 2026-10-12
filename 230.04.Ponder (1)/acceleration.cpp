/***********************************************************************
 * Source File:
 *    ACCELERATION
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about changing speed
 ************************************************************************/

#include "acceleration.h"
#include "angle.h"

#include <cmath>   // for sin() and cos()

 /*********************************************
  * ACCELERATION : ADD
  *  a += a
  *  Add another acceleration's horizontal and
  *  vertical components to this one.
  *********************************************/
void Acceleration::add(const Acceleration& acceleration)
{
	ddx += acceleration.ddx;
	ddy += acceleration.ddy;
}

/*********************************************
 * ACCELERATION : SET
 *  Set from angle and magnitude. An angle of 0
 *  points straight up, so sin() gives the
 *  horizontal part and cos() gives the vertical.
 *********************************************/
void Acceleration::set(const Angle& angle, double magnitude)
{
	// split the magnitude into horizontal and vertical components
	double radians = angle.getRadians();
	ddx = sin(radians) * magnitude;
	ddy = cos(radians) * magnitude;
}