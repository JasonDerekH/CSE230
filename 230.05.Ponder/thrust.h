/***********************************************************************
 * Header File:
 *    Thrust : Represents activation of thrusters
 * Author:
 *    Br. Helfrich
 * Summary:
 *    down, clockwise, and counterclockwise
 ************************************************************************/

#pragma once

#include "uiInteract.h"  // for Interface

#define THRUST 45000.00
#define WEIGHT 15103.00

class TestLander;
class TestThrust;

 /*****************************************************
  * THRUST
  * Represents activation of thrusters
  *****************************************************/
class Thrust
{
   friend TestLander;
   friend TestThrust;
   
public:
   // Thrust is initially turned off
   Thrust() : mainEngine(false), clockwise(false), counterClockwise(false) {}

   // Get rotation in radians per second
   double rotation() const
   {
	   double rotation = 0.0;

       if (clockwise)
		   rotation += 0.1;
	   if (counterClockwise)
		   rotation -= 0.1;

	   return rotation;
   }

   // get main engine thrust in  m / s ^ 2
   double mainEngineThrust() const
   {
      return mainEngine ? THRUST / WEIGHT : 0.0;
   }

   // reflect what is firing
   bool isMain()    const { return mainEngine; }
   bool isClock()   const { return clockwise; }
   bool isCounter() const { return counterClockwise; }

   // set the thrusters
   void set(const Interface * pUI)
   {
	  mainEngine       = pUI->isDown();
      clockwise        = pUI->isLeft();
	  counterClockwise = pUI->isRight();
   }

private:
   bool mainEngine;
   bool clockwise;
   bool counterClockwise;
};
