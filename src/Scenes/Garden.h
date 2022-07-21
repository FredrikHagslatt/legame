#ifndef GARDEN_H
#define GARDEN_H

#include "Scenes/Stardew.h"

class Garden : public Stardew
{
public:
    void UpdateScene(const double elapsedTime) override;
    void RenderScene(const double elapsedTime) override;
    void LoadScene() override;
    void UnloadScene() override;
    using Stardew::Stardew;
};

#endif