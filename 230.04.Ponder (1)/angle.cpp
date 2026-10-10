/***********************************************************************
 * Source File:
 *    ANGLE
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#include "angle.h"
#include <math.h>  // for floor()
#include <cassert>
using namespace std;

/************************************
 * ANGLE : NORMALIZE
 ************************************/
double Angle::normalize(double radians) const
{
    const double TWO_PI = 2.0 * M_PI;

    //fmod accounts for values more than a rotation as well as negatives (like % or abs() )
    radians = fmod(radians, TWO_PI);
    if (radians < 0.0)
        radians += TWO_PI;

    return radians;
}


