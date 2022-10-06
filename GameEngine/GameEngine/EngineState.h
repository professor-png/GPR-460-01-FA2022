#pragma once

#include "System_Common.h"
#include <SDL2/SDL.h>
#include <vector>

class GameObject;

struct EngineState
{
    SDL_Renderer* renderer = nullptr;
    gpr460::System* system = nullptr;
    std::vector<GameObject*> gameObjects;
    Uint32 frameStart = 0;
    bool quit = false;
    int frame = 0;

    ~EngineState();

    void Update(EngineState* engine);
};