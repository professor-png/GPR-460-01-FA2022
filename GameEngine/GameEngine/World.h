#pragma once

#include "GameObject.h"

const int MAX_OBJECTS = 2000;

struct World
{
	GameObject gameObjects[MAX_OBJECTS];

	Transform tranforms[MAX_OBJECTS];
	PlayerController playerControllers[MAX_OBJECTS];
	RectangleRenderer rectangleRenderer[MAX_OBJECTS];
	RectangleCollider rectangleColliders[MAX_OBJECTS];
	CollisionColorChanger collisionColorChangers[MAX_OBJECTS];

	void UpdateAll();
};