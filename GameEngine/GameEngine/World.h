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
private:
	typedef void (*compFn)(World* world, GameObject* go, std::istream& fin);
	std::unordered_map<int, World::compFn> componentMap;

public:
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
	
	GameObject* LoadGameObject(std::string name, Transform transform);
	static void AddPlayerController(World* world, GameObject* go, std::istream& fin);
	static void AddRectangleRenderer(World* world, GameObject* go, std::istream& fin);
	static void AddRectangleCollider(World* world, GameObject* go, std::istream& fin);
	static void AddCollisionColorChanger(World* world, GameObject* go, std::istream& fin);


	void LoadLevel(std::string fileName);
	void ReadLine(std::istream& line);
};