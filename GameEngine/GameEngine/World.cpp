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

World::~World()
{
	ShutDown();
}

void World::ShutDown()
{
	for (PlayerController player : playerControllers)
	{
		player.ShutDown();
	}

	for (RectangleCollider collider : rectangleColliders)
	{
		collider.ShutDown();
	}

	for (CollisionColorChanger colorChanger : collisionColorChangers)
	{
		colorChanger.ShutDown();
	}

	for (RectangleRenderer renderer : rectangleRenderers)
	{
		renderer.ShutDown();
	}

	for (GameObject object : gameObjects)
	{
		object.ShutDown();
	}
}

void World::UpdateAll(EngineState* engine)
{
	for (PlayerController player : playerControllers)
	{
		if (player.owner != nullptr)
			PlayerController::Update(&player, engine);
	}

	for (int i = 0; i < numActiveRectangleColliders; i++)
	{
		for (RectangleCollider collider : rectangleColliders)
		{
			if (collider.owner != nullptr && rectangleColliders[i].owner != nullptr && rectangleColliders[i].owner->GetName() != collider.owner->GetName())
			{
				rectangleColliders[i].SetColliding(rectangleColliders[i].owner->GetCollider()->CheckCollisions(collider.owner->GetCollider()));

				if (rectangleColliders[i].GetColliding())
					break;
			}
		}
	}
	
	for (CollisionColorChanger colorChanger : collisionColorChangers)
	{
		if (colorChanger.owner != nullptr && colorChanger.owner->GetCollider() != nullptr && colorChanger.owner->GetCollider()->GetColliding())
		{
			CollisionColorChanger::Update(&colorChanger, Color(0, 0, 255, 255));
		}
		else if (colorChanger.owner != nullptr && colorChanger.owner->GetCollider() != nullptr && !colorChanger.owner->GetCollider()->GetColliding())
			CollisionColorChanger::Update(&colorChanger, colorChanger.owner->GetRenderer()->originalColor);
	}

	for (RectangleRenderer renderer : rectangleRenderers)
	{
		if (renderer.owner != nullptr)
			RectangleRenderer::Draw(&renderer, engine);
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
		std::cout << collisionColorChangers[numActiveColorChangers].owner->GetName() << std::endl;
		numActiveColorChangers++;
	}
	return true;
}
