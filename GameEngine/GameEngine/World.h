#pragma once

#include "GameObject.h"
//#include "EngineState.h"
struct EngineState;
//class GameObject;

const int MAX_OBJECTS = 2000;

struct World
{
	int numActiveObjects = 0;
	int numActivePlayerControllers = 0;
	int numActiveRectangleRenderers = 0;
	int numActiveRectangleColliders = 0;
	int numActiveColorChangers = 0;

	GameObject gameObjects[MAX_OBJECTS];

	PlayerController playerControllers[MAX_OBJECTS];
	RectangleRenderer rectangleRenderers[MAX_OBJECTS];
	RectangleCollider rectangleColliders[MAX_OBJECTS];
	CollisionColorChanger collisionColorChangers[MAX_OBJECTS];

	World();
	~World();

	void UpdateAll(EngineState* engine);

	bool CreateGameObject(std::string name, Transform transform);
	bool AddPlayerController(int objIndex, PlayerController controller);
	bool AddRectangleRenderer(int objInex, RectangleRenderer renderer);
	bool AddRectangleCollider(int objInex, RectangleCollider collider);
	bool AddCollisionColorChanger(int objIndex, CollisionColorChanger colorChanger);
	
};