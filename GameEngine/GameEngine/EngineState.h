#pragma once

#include "System_Common.h"
#include <SDL2/SDL.h>
#include <vector>

class GameObject;

struct EngineState
{
    SDL_Renderer* renderer;
    gpr460::System* system;
    std::vector<GameObject*> gameObjects;
    Uint32 frameStart;
    bool quit;
    int frame;
};