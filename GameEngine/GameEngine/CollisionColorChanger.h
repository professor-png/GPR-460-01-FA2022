#pragma once
#include "EngineState.h"

class GameObject;
class RectangleRenderer;

class CollisionColorChanger
{
public:
	GameObject* owner = nullptr;

	void Update(EngineState* engine);
};