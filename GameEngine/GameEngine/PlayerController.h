#pragma once

#include "EngineState.h"

class GameObject;

class PlayerController
{
private:


public:
	PlayerController();

	void Update(EngineState* engine);
	static void Update(PlayerController* player, EngineState* engine);
	GameObject* owner = nullptr;
};