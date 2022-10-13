#include "World.h"
#include "EngineState.h"

World::World()
{
	numActiveObjects = 0;
	numActivePlayerControllers = 0;
	numActiveRectangleRenderers = 0;
	numActiveRectangleColliders = 0;
	numActiveColorChangers = 0;
}

void World::UpdateAll(EngineState* engine)
{
	for (PlayerController player : playerControllers)
	{
		player.Update(engine);
		//PlayerController::Update(&player, engine);
	}

	for (int i = 0; i < numActiveRectangleColliders; i++)
	{
		for (RectangleCollider collider : rectangleColliders)
		{
			if (rectangleColliders[i].owner->GetName() != collider.owner->GetName())
			{
				rectangleColliders[i].SetColliding(collider.owner->GetCollider()->CheckCollisions(collider.owner->GetCollider()));
			}
		}
	}

	for (CollisionColorChanger colorChanger : collisionColorChangers)
	{
		if (colorChanger.owner->GetCollider()->GetColliding())
			CollisionColorChanger::Update(&colorChanger, Color(0, 0, 255, 255));
	}

	for (RectangleRenderer renderer : rectangleRenderers)
	{
		renderer.Draw(engine);
		//RectangleRenderer::Draw(&renderer, engine);
	}

}

bool World::CreateGameObject(std::string name, Transform transform)
{
	if (numActiveObjects == MAX_OBJECTS - 1)
		return false;
	else
	{
		gameObjects[numActiveObjects] = GameObject(name, transform);
		numActiveObjects++;
	}
	return true;
}

bool World::AddPlayerController(int objIndex, PlayerController controller)
{
	if (numActivePlayerControllers == MAX_OBJECTS - 1)
		return false;
	else
	{
		playerControllers[numActivePlayerControllers] = controller;
		gameObjects[objIndex].CreatePlayerController(&playerControllers[numActivePlayerControllers]);
		numActivePlayerControllers++;
	}
	return true;
}

bool World::AddRectangleRenderer(int objIndex, RectangleRenderer renderer)
{
	if (numActiveRectangleRenderers == MAX_OBJECTS - 1)
		return false;
	else
	{
		rectangleRenderers[objIndex] = renderer;
		gameObjects[objIndex].CreateRenderer(&rectangleRenderers[objIndex]);
		numActiveRectangleRenderers++;
	}
	return true;
}

bool World::AddRectangleCollider(int objIndex, RectangleCollider collider)
{
	if (numActiveRectangleColliders == MAX_OBJECTS - 1)
		return false;
	else
	{
		rectangleColliders[numActiveRectangleColliders] = collider;
		gameObjects[objIndex].CreateCollider(&rectangleColliders[numActiveRectangleColliders]);
		numActiveRectangleColliders++;
	}
	return true;
}

bool World::AddCollisionColorChanger(int objIndex, CollisionColorChanger colorChanger)
{
	if (numActiveColorChangers == MAX_OBJECTS - 1)
		return false;
	else
	{
		collisionColorChangers[numActiveColorChangers] = colorChanger;
		gameObjects[objIndex].CreateColliderColorChanger(&collisionColorChangers[numActiveColorChangers]);
		numActiveColorChangers++;
	}
	return true;
}
