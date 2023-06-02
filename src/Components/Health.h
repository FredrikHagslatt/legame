#ifndef HEALTH_H
#define HEALTH_H

struct Health
{
    int hitPoints;
    Health(int hitPoints = 0)
        : hitPoints(hitPoints)
    {
    }
};

#endif