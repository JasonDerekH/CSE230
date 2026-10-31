#pragma once

struct Mapping
{
    double domain;
    double range;
};

double linearInterpolation(double d0, double r0,
    double d1, double r1,
    double d);

// Find where d falls in a sorted table and interpolate
double linearInterpolation(const Mapping mapping[], int numMapping, double d);

double gravityFromAltitude(double altitude);

double areaFromDiameter(double diameter);

double forceFromDrag(double density, double area, double diameter, double velocity);

double accelerationFromForce(double force, double mass);

double densityFromAltitude(double altitude);

double speedSoundFromAltitude(double altitude);

double dragFromMach(double speedMach);