#include "EngineState.h"
#include "GameObject.h"
#include "World.h"

EngineState::EngineState()
{

}

EngineState::~EngineState()
{
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


    renderer = nullptr;
    system = nullptr;
}

void EngineState::Update(EngineState* engine)
{
    /*for (int i = (int)gameObjects->size() - 1; i >= 0; i--)
    {
        gameObjects->at(i)->Update(engine);
    }*/

    world.UpdateAll(engine);
}