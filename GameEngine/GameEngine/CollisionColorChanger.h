#pragma once
#include "EngineState.h"

class GameObject;
class RectangleRenderer;

class CollisionColorChanger
{
public:
	GameObject* owner = nullptr;

	CollisionColorChanger();
	void Update(EngineState* engine);
};