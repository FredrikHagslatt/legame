#ifndef GARDEN_H
#define GARDEN_H

#include "Scenes/Stardew.h"

class Garden : public Stardew
{
public:
    void UpdateScene(double elapsedTime) override;
    void RenderScene(double elapsedTime) override;
    void LoadScene() override;
    void UnloadScene() override;
    using Stardew::Stardew;
};

#endif