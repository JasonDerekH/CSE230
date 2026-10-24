/***********************************************************************
 * Header File:
 *    STAR
 * Author:
 *    Br. Helfrich, modified by Riley Cluff
 * Summary:
 *    A single star that twinkles
 ************************************************************************/

#pragma once

#include "position.h" // for POSITION
#include "uiDraw.h"   // for RANDOM and DRAWSTAR

/*****************************************************
 * STAR
 * A star that twinkles
 *****************************************************/
class Star
{
 public:
   /*********************************************
    * name:    DEFAULT CONSTRUCTOR
    * input:   nothing
    * output:  a star at the origin
    *********************************************/
   Star() : pos(), phase((unsigned char)random(0, 255)) {}

   /*********************************************
    * name:    POSITIONED CONSTRUCTOR
    * input:   screen width and height
    * output:  a star positioned on the screen
    *********************************************/
   Star(double width, double height) : Star()
   {
      reset(width, height);
   }

   /*********************************************
    * name:    RESET
    * input:   screen width and height
    * output:  a random position and phase
    *********************************************/
   void reset(double width, double height)
   {
      pos.setX(random(0.0, width));
      pos.setY(random(0.0, height));
      phase = (unsigned char)random(0, 255);
   }

   /*********************************************
    * name:    DRAW
    * input:   graphics stream
    * output:  draws the star and advances its phase
    *********************************************/
   void draw(ogstream &gout)
   {
      gout.drawStar(pos, phase);
      phase++;
   }

 private:
   Position pos;        // where the star is on the screen
   unsigned char phase; // animation frame for the twinkling star
};
