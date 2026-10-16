/**********************************************************************
 * Source File:
 *    LAB 06
 * Author:
 *    Br. Helfrich, modified by Riley Cluff
 * Summary:
 *    Lunar Lander simulation. This is the Simulator class and main()
 **********************************************************************/

#include "position.h"      // everything should have a point
#include "angle.h"         // angle of the lander
#include "uiInteract.h"    // for INTERFACE
#include "uiDraw.h"        // for RANDOM and DRAW*
#include "ground.h"        // for GROUND
#include "lander.h"        // for LANDER
#include "thrust.h"        // for THRUST
#include "acceleration.h"  // for ACCELERATION
#include "star.h"          // for STAR
#include "test.h"          // for the unit tests
#include <cmath>           // for SQRT
#include <cassert>         // for ASSERT
using namespace std;

#define GRAVITY    -1.625   // gravity on the moon, in m/s^2
#define TIME        0.1     // seconds per frame
#define NUM_STARS   50      // how many stars in the sky

/*************************************************************************
 * SIMULATOR
 * Everything pertaining to the simulator.
 *************************************************************************/
class Simulator
{
public:
    // set up the simulator
    Simulator(const Position& posUpperRight) :
        ground(posUpperRight),
        lander(posUpperRight)
    {
        // the lander starts out of play, so put it on the board
        lander.reset(posUpperRight);

        // scatter the stars across the sky
        for (Star& star : stars)
            star.reset(posUpperRight.getX(), posUpperRight.getY());
    }

    // display stuff on the screen
    void display();

    // move the lander one frame
    void move(const Interface* pUI);

    Star stars[NUM_STARS];  // the twinkling stars
    Ground ground;          // the lunar surface
    Lander lander;          // the lunar module
    Thrust thrust;          // which thrusters are firing
};

/**********************************************************
 * SIMULATOR : DISPLAY
 * Draw the stars, the ground, and the lander on the screen
 **********************************************************/
void Simulator::display()
{
    ogstream gout;

    // draw the stars first so everything else is in front of them
    for (Star& star : stars)
        star.draw(gout);

    // draw the ground
    ground.draw(gout);

    // draw the lander and its flames
    lander.draw(thrust, gout);
}

/**********************************************************
 * SIMULATOR : MOVE
 * Read the controls, apply physics, move the lander,
 * and check whether we have landed or crashed
 **********************************************************/
void Simulator::move(const Interface* pUI)
{
    // see which thrusters the user is firing
    thrust.set(pUI);

    // once we have landed or crashed, nothing moves
    if (!lander.isFlying())
        return;

    // apply the physics for this frame
    Acceleration acceleration = lander.input(thrust, GRAVITY);
    lander.coast(acceleration, TIME);

    // touched the landing pad: safe if slow enough, dead if not
    if (ground.onPlatform(lander.getPosition(), lander.getWidth()))
    {
        if (lander.getSpeed() <= lander.getMaxSpeed())
            lander.land();
        else
            lander.crash();
    }
    // touched anywhere else on the ground: dead
    else if (ground.hitGround(lander.getPosition(), lander.getWidth()))
        lander.crash();
}

/*************************************
 * CALLBACK
 * Handle one frame of the simulator
 **************************************/
void callBack(const Interface* pUI, void* p)
{
    // the first step is to cast the void pointer into a simulator object.
    // This is the first step of every single callback function in OpenGL.
    Simulator* pSimulator = (Simulator*)p;

    // move the lander, then draw everything
    pSimulator->move(pUI);
    pSimulator->display();
}

/*********************************
 * MAIN
 * Main is pretty sparse.  Just initialize
 * my LM type and call the display engine.
 * That is all!
 *********************************/
#ifdef _WIN32
#include <windows.h>
int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR pCmdLine,
    _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
    // Run the unit tests
    testRunner();

    // Initialize OpenGL
    Position posUpperRight(400, 400);
    Interface ui("Lunar Lander", posUpperRight);

    // Initialize the game class
    Simulator simulator(posUpperRight);

    // set everything into action
    ui.run(callBack, (void*)&simulator);

    return 0;
}