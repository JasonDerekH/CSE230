#pragma once

class Velocity;
class Acceleration;

class Position
{
public:
   Position() : x_(0.0), y_(0.0) {}
   Position(double x, double y) : x_(x), y_(y) {}

   double x() const { return x_; }
   double y() const { return y_; }
   void setX(double x) { x_ = x; }
   void setY(double y) { y_ = y; }

   void advance(const Velocity& velocity, const Acceleration& acceleration, double dt);

private:
   double x_;
   double y_;
};
