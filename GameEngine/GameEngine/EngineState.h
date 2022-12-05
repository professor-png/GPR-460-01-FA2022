#pragma once

#include "System.h"
#include <vector>

#include "StackAllocator.h"

#include "EditorGui.h"

class GameObject;
struct World;

struct EngineState
{
    SDL_Renderer* renderer = nullptr;
    gpr460::System* system = nullptr;
    std::vector<GameObject*> gameObjects;
    World world;
    EditorGui gui;
    StackAllocator objectPool;
    Uint32 frameStart = 0;
    bool quit = false;
    int frame = 0;

    EngineState();
    ~EngineState();

    void ShutDown();
    void InitGui(SDL_Window* window, SDL_Renderer* renderer);
    void PollGuiEvents(SDL_Event& event);
    void Update(EngineState* engine);
};