#include "EngineState.h"
#include "GameObject.h"
#include "World.h"

EngineState::EngineState()
{
    gameObjects = new std::vector<GameObject*>();
}

EngineState::~EngineState()
{
    ShutDown();
}

void EngineState::ShutDown()
{
    //objectPool.clear();
    if (gameObjects != nullptr)
    {
        for (auto& obj : *gameObjects)
        {
            obj->~GameObject();
        }
        objectPool.clear();
        gameObjects->clear();
        delete gameObjects;
        gameObjects = nullptr;
    }


    renderer = nullptr;
    system = nullptr;
}

void EngineState::Update(EngineState* engine)
{
    for (int i = (int)gameObjects->size() - 1; i >= 0; i--)
    {
        gameObjects->at(i)->Update(engine);
    }

    world.UpdateAll(engine);
}