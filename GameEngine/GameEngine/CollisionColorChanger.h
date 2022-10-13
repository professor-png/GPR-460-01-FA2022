#pragma once
#include "EngineState.h"

class GameObject;
class RectangleRenderer;
struct Color;

class CollisionColorChanger
{
public:
	GameObject* owner = nullptr;

	CollisionColorChanger();
	void Update(Color color);
	static void Update(CollisionColorChanger* colorChanger, Color color);
};