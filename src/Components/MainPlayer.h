#ifndef MAINPLAYER_H
#define MAINPLAYER_H

struct MainPlayer
{
    MainPlayer() = default;
    uint8_t bugPreventer = 0;
    // For some reason, having an empty component prevents the map to render.
};

#endif