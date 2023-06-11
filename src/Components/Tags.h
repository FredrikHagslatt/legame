#ifndef TAGS_H
#define TAGS_H

struct KeyboardControlled_Tag
{
};
struct Crosshair_Tag
{
};
struct Player_Tag
{
};
struct Enemy_Tag
{
};
struct Obstacle_Tag
{
};
struct Projectile_Tag
{
};
struct StayOnMap_Tag
{
};
struct Trigger_Tag
{
};
struct LiveSpell_Tag
{
};

// Rendering order. Renderable entities without there tags are considered Grounded.
// Rendering order are the: Grounded, Airborne, Effect, UI
struct Airborne_Tag
{
};
struct Effect_Tag
{
};
struct UI_Tag
{
};

#endif