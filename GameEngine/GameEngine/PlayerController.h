#pragma once

#include "System.h"

class PlayerController
{
public:
	void Update(EngineState* engine);
	GameObject* owner;
};