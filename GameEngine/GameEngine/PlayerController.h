#pragma once

#include "EngineState.h"

class GameObject;

class PlayerController
{
private:


public:
	PlayerController();

	void Update(EngineState* engine);
	GameObject* owner = nullptr;
};