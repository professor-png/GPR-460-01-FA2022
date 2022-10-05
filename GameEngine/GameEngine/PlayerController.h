#pragma once

#include "EngineState.h"

class GameObject;

class PlayerController
{
private:


public:
	void Update(EngineState* engine);
	GameObject* owner;
};