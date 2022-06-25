#ifndef HEALTH_H
#define HEALTH_H

struct Health
{
    int healthPercentage;
    Health(int healthPercentage = 0)
    : healthPercentage(healthPercentage)
    {

    }
};

#endif