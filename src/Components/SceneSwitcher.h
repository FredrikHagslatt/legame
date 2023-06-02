#ifndef SCENESWITCHER_H
#define SCENESWITCHER_H

#include <string>
struct SceneSwitcher
{
    std::string sceneManagerId;
    std::string sceneName;
    SceneSwitcher(std::string sceneManagerId = "", std::string sceneName = "") : sceneManagerId(sceneManagerId), sceneName(sceneName)
    {
    }
};

#endif