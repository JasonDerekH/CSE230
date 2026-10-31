/***********************************************************************
 * Header File:
 *    Thrust : Represents activation of thrusters
 * Author:
 *    Br. Helfrich
 * Summary:
 *    down, clockwise, and counterclockwise
 ************************************************************************/

#pragma once

#include "uiInteract.h" // for Interface

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
   /*********************************************
    * name:    CONSTRUCTOR
    * input:   nothing
    * output:  all thrusters off
    *********************************************/
   Thrust() : mainEngine(false), clockwise(false), counterClockwise(false) {}

   /*********************************************
    * name:    ROTATION
    * input:   current thruster state
    * output:  rotation in radians per second
    *********************************************/
   double rotation() const
   {
      double rotation = 0.0;

      if (clockwise)
         rotation += 0.1;
      if (counterClockwise)
         rotation -= 0.1;

      return rotation;
   }

   /*********************************************
    * name:    MAIN ENGINE THRUST
    * input:   current main-engine state
    * output:  thrust in meters per second squared
    *********************************************/
   double mainEngineThrust() const
   {
      return mainEngine ? THRUST / WEIGHT : 0.0;
   }

   /*********************************************
    * name:    IS MAIN
    * input:   nothing
    * output:  whether the main engine is firing
    *********************************************/
   bool isMain() const { return mainEngine; }

   /*********************************************
    * name:    IS CLOCK
    * input:   nothing
    * output:  whether the clockwise thruster is firing
    *********************************************/
   bool isClock() const { return clockwise; }

   /*********************************************
    * name:    IS COUNTER
    * input:   nothing
    * output:  whether the counterclockwise thruster is firing
    *********************************************/
   bool isCounter() const { return counterClockwise; }

   /*********************************************
    * name:    SET
    * input:   user interface
    * output:  updates the thruster states
    *********************************************/
   void set(const Interface *pUI)
   {
      mainEngine = pUI->isDown();
      clockwise = pUI->isLeft();
      counterClockwise = pUI->isRight();
   }

 private:
   bool mainEngine;
   bool clockwise;
   bool counterClockwise;
};
