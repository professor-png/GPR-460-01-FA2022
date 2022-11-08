#include "EngineState.h"
#include "GameObject.h"
#include "World.h"


EngineState::~EngineState()
{
    ShutDown();
}

void EngineState::ShutDown()
{
    //objectPool.clear();
    for (auto obj : gameObjects)
    {
        delete obj;
    }
    gameObjects.clear();

    renderer = nullptr;
    system = nullptr;
}

void EngineState::Update(EngineState* engine)
{
    for (int i = (int)gameObjects.size() - 1; i >= 0; i--)
    {
        gameObjects[i]->Update(engine);
    }

    world.UpdateAll(engine);
}