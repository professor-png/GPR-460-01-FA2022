#include "EngineState.h"
#include "GameObject.h"
#include "World.h"

EngineState::EngineState()
{
    
}

EngineState::~EngineState()
{
    gui.ShutDown();
    ShutDown();
}

void EngineState::ShutDown()
{
    //objectPool.clear();
    for (auto obj : gameObjects)
    {
        obj->~GameObject();
    }
    objectPool.clear();
    gameObjects.clear();

    //gui.ShutDown();

    renderer = nullptr;
    system = nullptr;
}

void EngineState::InitGui(SDL_Window* window, SDL_Renderer* renderer)
{
    gui.InitGui(window, renderer);
}

void EngineState::PollGuiEvents(SDL_Event& event)
{
    ImGui_ImplSDL2_ProcessEvent(&event);
}

void EngineState::Update(EngineState* engine)
{
    /*for (int i = (int)gameObjects->size() - 1; i >= 0; i--)
    {
        gameObjects->at(i)->Update(engine);
    }*/

    world.UpdateAll(engine);
    gui.DrawGui(&engine->world);
}