#ifndef VELOCITY_H
#define VELOCITY_H

struct Velocity
{
    double x;
    double y;

    Velocity(double x = 0, double y = 0)
        : x(x), y(y)
    {
    }
};

#endif