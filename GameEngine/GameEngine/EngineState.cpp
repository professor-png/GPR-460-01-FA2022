#include "EngineState.h"
#include "GameObject.h"


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
    for (auto obj : gameObjects)
    {
        obj->Update(engine);
    }
}