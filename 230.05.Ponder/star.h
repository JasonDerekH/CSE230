/***********************************************************************
 * Header File:
 *    STAR
 * Author:
 *    Br. Helfrich, modified by Riley Cluff
 * Summary:
 *    A single star that twinkles
 ************************************************************************/

#pragma once

#include "position.h"   // for POSITION
#include "uiDraw.h"     // for RANDOM and DRAWSTAR

 /*****************************************************
  * STAR
  * A star that twinkles
  *****************************************************/
class Star
{
public:
    // Default: start at the origin with a random phase
    Star() : pos(), phase((unsigned char)random(0, 255)) {}

    // Convenience: create a star already placed on the screen
    Star(double width, double height) : Star()
    {
        reset(width, height);
    }

    // Move to a random location with a random phase
    void reset(double width, double height)
    {
        pos.setX(random(0.0, width));
        pos.setY(random(0.0, height));
        phase = (unsigned char)random(0, 255);
    }

    // Draw the star, then advance its phase so it twinkles
    void draw(ogstream& gout)
    {
        gout.drawStar(pos, phase);
        phase++;
    }

private:
    Position pos;           // where the star is on the screen
    unsigned char phase;    // animation frame for the twinkling star
};