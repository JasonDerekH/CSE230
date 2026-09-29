/*************************************************************
 * 1. Name:
 *      Jason Hollingsworth & Riley Cluff
 * 2. Assignment Name:
 *      Lab 02: Apollo 11
 * 3. Assignment Description:
 *      Simulate the Apollo 11 landing
 * 4. What was the hardest part? Be as specific as possible.
 *      The assignment went well, the hardest part of the assignment
 * was the implementation of the simulate funciton. Making sure that 
 I could go for 5 seconds and then continue after entering a new angle.
 * 5. How long did it take for you to complete the assignment?
 *      3.5 hours
 *****************************************************************/

#include <iostream>  // for CIN and COUT
#include <cmath>     // for SIN, COS, SQRT, POW
#include <numbers>   // for PI
#include <string>    // for STRING
using namespace std;

#define WEIGHT   15103.000   // Weight in KG
#define GRAVITY     -1.625   // Vertical acceleration due to gravity, in m/s^2
#define THRUST   45000.000   // Thrust of main engine, in Newtons (kg m/s^2)

const double TIME_INTERVAL = 1.0;   // Seconds between each simulation step
const int    NUM_STEPS = 5;     // Seconds simulated before the pilot rotates

/***************************************************
 * COMPUTE DISTANCE
 * Apply inertia to compute a new position using the distance equation.
 * The equation is:
 *     s = s + v t + 1/2 a t^2
 * INPUT
 *     s : original position, in meters
 *     v : velocity, in meters/second
 *     a : acceleration, in meters/second^2
 *     t : time, in seconds
 * OUTPUT
 *     s : new position, in meters
 **************************************************/
double computeDistance(double position, double velocity, double acceleration, double time)
{
    return position + velocity * time + 0.5 * acceleration * pow(time, 2);
}

/**************************************************
 * COMPUTE ACCELERATION
 * Find the acceleration given a thrust and mass.
 * This will be done using Newton's second law of motion:
 *     f = m * a
 * INPUT
 *     f : force, in Newtons (kg * m / s^2)
 *     m : mass, in kilograms
 * OUTPUT
 *     a : acceleration, in meters/second^2
 ***************************************************/
double computeAcceleration(double force, double mass)
{
    return force / mass;
}

/***********************************************
 * COMPUTE VELOCITY
 * Starting with a given velocity, find the new
 * velocity once acceleration is applied. This is
 * called the Kinematics equation. The
 * equation is:
 *     v = v + a t
 * INPUT
 *     v : velocity, in meters/second
 *     a : acceleration, in meters/second^2
 *     t : time, in seconds
 * OUTPUT
 *     v : new velocity, in meters/second
 ***********************************************/
double computeVelocity(double velocity, double acceleration, double time)
{
    return velocity + acceleration * time;
}

/***********************************************
 * COMPUTE VERTICAL COMPONENT
 * Find the vertical component of a velocity or acceleration.
 * The equation is:
 *     cos(a) = y / total
 * This can be expressed graphically:
 *      x
 *    +-----
 *    |   /
 *  y |  / total
 *    |a/
 *    |/
 * INPUT
 *     a : angle, in radians
 *     total : total velocity or acceleration
 * OUTPUT
 *     y : the vertical component of the total
 ***********************************************/
double computeVerticalComponent(double angle, double total)
{
    return cos(angle) * total;
}

/***********************************************
 * COMPUTE HORIZONTAL COMPONENT
 * Find the horizontal component of a velocity or acceleration.
 * The equation is:
 *     sin(a) = x / total
 * This can be expressed graphically:
 *      x
 *    +-----
 *    |   /
 *  y |  / total
 *    |a/
 *    |/
 * INPUT
 *     a : angle, in radians
 *     total : total velocity or acceleration
 * OUTPUT
 *     x : the horizontal component of the total
 ***********************************************/
double computeHorizontalComponent(double angle, double total)
{
    return sin(angle) * total;
}

/************************************************
 * COMPUTE TOTAL COMPONENT
 * Given the horizontal and vertical components of
 * something (velocity or acceleration), determine
 * the total component. To do this, use the Pythagorean Theorem:
 *    x^2 + y^2 = t^2
 * where:
 *      x
 *    +-----
 *    |   /
 *  y |  / total
 *    | /
 *    |/
 * INPUT
 *    x : horizontal component
 *    y : vertical component
 * OUTPUT
 *    total : total component
 ***********************************************/
double computeTotalComponent(double horizontal, double vertical)
{
    return sqrt(pow(horizontal, 2) + pow(vertical, 2));
}

/*************************************************
 * RADIANS FROM DEGEES
 * Convert degrees to radians:
 *     radians / 2pi = degrees / 360
 * INPUT
 *     d : degrees from 0 to 360
 * OUTPUT
 *     r : radians from 0 to 2pi
 **************************************************/
double radiansFromDegrees(double degrees)
{
    return degrees / 360.0 * 2.0 * numbers::pi;
}

/**************************************************
 * PROMPT
 * A generic function to prompt the user for a double
 * INPUT
 *      message : the message to display to the user
 * OUTPUT
 *      response : the user's response
 ***************************************************/
double prompt(string message)
{
    double response = 0.0;
    cout << message;
    cin >> response;
    return response;
}

/**************************************************
 * SIMULATE
 * Run the simulation for NUM_STEPS seconds with the
 * main engine on, displaying the state of the LM
 * after each time interval.
 * INPUT
 *      x, y      : position, in meters
 *      dx, dy    : velocity, in meters/second
 *      aDegrees  : angle of the LM, in degrees (0 is up)
 *      startTime : seconds already elapsed in the simulation
 * OUTPUT
 *      x, y, dx, dy : updated position and velocity (by reference)
 ***************************************************/
void simulate(double& x, double& y, double& dx, double& dy,
    double aDegrees, int startTime)
{
    // Acceleration depends only on the angle, so compute it once
    double aRadians = radiansFromDegrees(aDegrees);
    double accelerationThrust = computeAcceleration(THRUST, WEIGHT);
    double ddx = computeHorizontalComponent(aRadians, accelerationThrust);
    double ddy = computeVerticalComponent(aRadians, accelerationThrust)
        + GRAVITY;

    cout << "\nFor the next " << NUM_STEPS
        << " seconds with the main engine on, "
        << "the position of the lander is:\n\n";

    for (int second = 1; second <= NUM_STEPS; second++)
    {
        // Update the position before updating the velocity
        x = computeDistance(x, dx, ddx, TIME_INTERVAL);
        y = computeDistance(y, dy, ddy, TIME_INTERVAL);
        dx = computeVelocity(dx, ddx, TIME_INTERVAL);
        dy = computeVelocity(dy, ddy, TIME_INTERVAL);
        double speed = computeTotalComponent(dx, dy);

        // Pad single-digit times with a space so the columns line up
        int time = startTime + second;
        if (time < 10)
            cout << " ";

        cout << time << "s - "
            << "x,y:(" << x << ", " << y << ")m  "
            << "dx,dy:(" << dx << ", " << dy << ")m/s  "
            << "speed:" << speed << "m/s  "
            << "angle:" << aDegrees << "deg\n";
    }
}

/****************************************************************
 * MAIN
 * Prompt for input, simulate the descent, then let the pilot
 * rotate the LM and simulate the rest of the descent
 ****************************************************************/
int main()
{
    // Prompt for the initial state of the LM
    double dy = prompt("What is your vertical velocity (m/s)? ");
    double dx = prompt("What is your horizontal velocity (m/s)? ");
    double y = prompt("What is your altitude (m)? ");
    double x = 0.0;   // Horizontal position starts at 0
    double aDegrees = prompt("What is the angle of the LM where 0 is up (degrees)? ");

    cout.setf(ios::fixed | ios::showpoint);
    cout.precision(2);

    // First five seconds of flight
    simulate(x, y, dx, dy, aDegrees, 0);

    // Let the pilot rotate the LM, then run five more seconds
    cout << endl;
    aDegrees = prompt("What is the new angle of the LM where 0 is up (degrees)? ");
    simulate(x, y, dx, dy, aDegrees, NUM_STEPS);

    return 0;
}