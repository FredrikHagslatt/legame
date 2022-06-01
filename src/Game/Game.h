#ifndef GAME_H
#define GAME_H

#include "Logger/Logger.h"
#include "ECS/ECS.h"
#include <glm/glm.hpp>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000 / FPS;
class Game
{
private:
    bool isRunning;
    double deltaTime = 0;
    int millisecsPreviousFrame = 0;
    SDL_Window* window;
    SDL_Renderer* renderer;
 
public:
    Game();
    ~Game();
    void Initialize();
    void Run();
    void Setup();
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();

    int windowWidth;
    int windowHeight;
};

#endif