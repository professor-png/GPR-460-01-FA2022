#include "EngineState.h"
#include "GameObject.h"
#include "World.h"


EngineState::~EngineState()
{
    for (auto obj : gameObjects)
    {
        delete obj;
    }
    gameObjects.clear();
}

void EngineState::Update(EngineState* engine)
{
    //for (int i = (int)gameObjects.size() - 1; i >= 0; i--)
    //{
    //    gameObjects[i]->Update(engine);
    //}

    world.UpdateAll(engine);
}