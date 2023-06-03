#ifndef SCENESWITCHER_H
#define SCENESWITCHER_H

#include <string>
struct SceneSwitcher
{
    std::string sceneManagerId;
    std::string sceneName;
    std::string level;
    SceneSwitcher(std::string sceneManagerId = "", std::string sceneName = "", std::string level = "")
        : sceneManagerId(sceneManagerId), sceneName(sceneName), level(level)
    {
    }
};

#endif