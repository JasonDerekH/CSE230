/***********************************************************************
 * Header File:
 *    LANDER
 * Author:
 *    Br. Helfrich
 * Summary:
 *    All the information about the lunar lander
 ************************************************************************/

#pragma once

#include "angle.h"    // for ANGLE
#include "position.h" // for POINT
#include "thrust.h"   // for THRUST
#include "uiDraw.h"   // for DRAW* and RANDOM
#include "velocity.h" // for VELOCITY

enum Status
{
   PLAYING,
   SAFE,
   DEAD
};

class TestLander;

/****************************************************************
 * LANDER
 * The position and status of the lander
 ***************************************************************/
class Lander
{
   friend TestLander;

 public:
   /*********************************************
    * name:    CONSTRUCTOR
    * input:   upper-right corner of the board
    * output:  an inactive lander
    *********************************************/
   Lander(const Position &posUpperRight) : status(DEAD), fuel(0.0) {}

   /*********************************************
    * name:    RESET
    * input:   upper-right corner of the board
    * output:  a new flying lander
    *********************************************/
   void reset(const Position &posUpperRight);

   /*********************************************
    * name:    IS DEAD
    * input:   nothing
    * output:  whether the lander is dead
    *********************************************/
   bool isDead() const { return status == DEAD; }

   /*********************************************
    * name:    IS LANDED
    * input:   nothing
    * output:  whether the lander is safe
    *********************************************/
   bool isLanded() const { return status == SAFE; }

   /*********************************************
    * name:    IS FLYING
    * input:   nothing
    * output:  whether the lander is flying
    *********************************************/
   bool isFlying() const { return status == PLAYING; }

   /*********************************************
    * name:    GET POSITION
    * input:   nothing
    * output:  the lander's position
    *********************************************/
   Position getPosition() const { return pos; }

   /*********************************************
    * name:    GET SPEED
    * input:   nothing
    * output:  the lander's speed
    *********************************************/
   double getSpeed() const { return velocity.getSpeed(); }

   /*********************************************
    * name:    GET FUEL
    * input:   nothing
    * output:  remaining fuel
    *********************************************/
   int getFuel() const { return (int)fuel; }

   /*********************************************
    * name:    GET WIDTH
    * input:   nothing
    * output:  lander width
    *********************************************/
   int getWidth() const { return 20; }

   /*********************************************
    * name:    GET MAX SPEED
    * input:   nothing
    * output:  maximum safe landing speed
    *********************************************/
   double getMaxSpeed() const { return 4.0; }

   /*********************************************
    * name:    DRAW
    * input:   thrust state and graphics stream
    * output:  draws the lander
    *********************************************/
   void draw(const Thrust &thrust, ogstream &gout) const;

   /*********************************************
    * name:    INPUT
    * input:   thrust state and gravity
    * output:  resulting acceleration
    *********************************************/
   Acceleration input(const Thrust &thrust, double gravity);

   /*********************************************
    * name:    COAST
    * input:   acceleration and time
    * output:  updates position and velocity
    *********************************************/
   void coast(Acceleration &acceleration, double time);

   /*********************************************
    * name:    LAND
    * input:   nothing
    * output:  marks the lander as safely landed
    *********************************************/
   void land()
   {
      angle.setRadians(0.0);
      status = SAFE;
   }

   /*********************************************
    * name:    CRASH
    * input:   nothing
    * output:  marks the lander as dead
    *********************************************/
   void crash()
   {
      angle.setRadians(M_PI);
      status = DEAD;
   }

 private:
   Status status;     // are we dead or not?
   Position pos;      // the location of the lander
   Velocity velocity; // the speed of the lander
   Angle angle;       // the orientation of the lander
   double fuel;       // amount of fuel remaining
};
