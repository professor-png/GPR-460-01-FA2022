#pragma once

#include "GameObject.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <unordered_map>

struct EngineState;

const int MAX_OBJECTS = 100;
const int NUM_COMPONENTS = 4;

enum CompId
{
	ColliderId = 'COLL',
	RendererId = 'REND',
	PlayerControllerId = 'PCON',
	ColorChangerId = 'COLC',
};

struct World
{
	typedef void (*compFn)(GameObject* go, std::istream& fin);

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

	void ShutDown();
	void UpdateAll(EngineState* engine);

	bool CreateGameObject(std::string name, Transform transform);
	bool AddPlayerController(int objIndex, PlayerController controller);
	bool AddRectangleRenderer(int objInex, RectangleRenderer renderer);
	bool AddRectangleCollider(int objInex, RectangleCollider collider);
	bool AddCollisionColorChanger(int objIndex, CollisionColorChanger colorChanger);
	
	static void AddPlayerController(GameObject* go, std::istream& fin);
	static void AddRectangleRenderer(GameObject* go, std::istream& fin);
	static void AddRectangleCollider(GameObject* go, std::istream& fin);
	static void AddCollisionColorChanger(GameObject* go, std::istream& fin);


	void LoadLevel(std::string fileName);
	void ReadLine(std::istream& line);
};