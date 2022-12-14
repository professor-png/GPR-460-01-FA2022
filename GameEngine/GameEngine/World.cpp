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
		rectangleRenderers[numActiveRectangleRenderers] = renderer;
		gameObjects[objIndex].CreateRenderer(&rectangleRenderers[numActiveRectangleRenderers]);
		numActiveRectangleRenderers++;
	}
	return true;
}

void World::DeleteGameObject(std::string name)
{
	int index = -1;
	for (int i = 0; i < numActiveObjects; i++)
	{
		if (gameObjects[i].GetName() == name)
		{
			index = i;
			break;
		}
	}
	if (index == -1)
	{
		return;
	}

	if (gameObjects[index].GetCollider() != nullptr)
		DeleteRectangleCollider(gameObjects[index].GetName());

	if (gameObjects[index].GetRenderer() != nullptr)
		DeleteRectangleRenderer(gameObjects[index].GetName());

	if (gameObjects[index].GetPlayerController() != nullptr)
		DeletePlayerController(gameObjects[index].GetName());

	if (gameObjects[index].GetCollisionColorChanger() != nullptr)
		DeleteColorChanger(gameObjects[index].GetName());

	gameObjects[index].ShutDown();
	for (int i = index; i < numActiveObjects - 1; i++)
	{
		gameObjects[i] = gameObjects[i + 1];
	}
	numActiveObjects--;
}

void World::DeleteRectangleRenderer(std::string name) 
{
	int index = -1;
	for (int i = 0; i < numActiveRectangleRenderers; i++) 
	{
		if (rectangleRenderers[i].owner->GetName() == name) 
		{
			index = i;
			break;
		}
	}
	if (index == -1) 
	{
		return;
	}
	rectangleRenderers[index].ShutDown();
	for (int i = index; i < numActiveRectangleRenderers; i++)
	{
		rectangleRenderers[i] = rectangleRenderers[i + 1];
		if (rectangleRenderers[i].owner != nullptr)
			rectangleRenderers[i].owner->SetRenderer(&rectangleRenderers[i]);
	}
	numActiveRectangleRenderers--;
}

void World::DeleteRectangleCollider(std::string name)
{
	int index = -1;
	for (int i = 0; i < numActiveRectangleColliders; i++)
	{
		if (rectangleColliders[i].owner->GetName() == name)
		{
			index = i;
			break;
		}
	}
	if (index == -1)
	{
		return;
	}
	rectangleColliders[index].ShutDown();
	for (int i = index; i < numActiveRectangleColliders; i++)
	{
		rectangleColliders[i] = rectangleColliders[i + 1];
		if (rectangleColliders[i].owner != nullptr)
			rectangleColliders[i].owner->SetCollider(&rectangleColliders[i]);
	}
	numActiveRectangleColliders--;
}

void World::DeletePlayerController(std::string name)
{
	int index = -1;
	for (int i = 0; i < numActivePlayerControllers; i++)
	{
		if (playerControllers[i].owner->GetName() == name)
		{
			index = i;
			break;
		}
	}
	if (index == -1)
	{
		return;
	}
	playerControllers[index].ShutDown();
	for (int i = index; i < numActivePlayerControllers; i++)
	{
		playerControllers[i] = playerControllers[i + 1];
		if (playerControllers[i].owner != nullptr)
			playerControllers[i].owner->SetPlayerController(&playerControllers[i]);
	}
	numActivePlayerControllers--;
}

void World::DeleteColorChanger(std::string name)
{
	int index = -1;
	for (int i = 0; i < numActiveColorChangers; i++)
	{
		if (collisionColorChangers[i].owner->GetName() == name)
		{
			index = i;
			break;
		}
	}
	if (index == -1)
	{
		return;
	}
	collisionColorChangers[index].ShutDown();
	for (int i = index; i < numActiveColorChangers; i++)
	{
		collisionColorChangers[i] = collisionColorChangers[i + 1];
		if (collisionColorChangers[i].owner != nullptr)
			collisionColorChangers[i].owner->SetColorChanger(&collisionColorChangers[i]);
	}
	numActiveColorChangers--;
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

// static functions
GameObject* World::LoadGameObject(std::string name, Transform transform)
{
	if (numActiveObjects == MAX_OBJECTS - 1)
		return nullptr;
	else
	{
		gameObjects[numActiveObjects] = GameObject(name, transform);
		numActiveObjects++;
	}

	return &gameObjects[numActiveObjects - 1];
}

void World::AddPlayerController(World* world, GameObject* go, std::istream& fin)
{
	if (world->numActivePlayerControllers == MAX_OBJECTS - 1)
		return;
	else
	{
		world->playerControllers[world->numActivePlayerControllers] = PlayerController();
		go->CreatePlayerController(&world->playerControllers[world->numActivePlayerControllers]);
		world->numActivePlayerControllers++;
	}
}

void World::AddRectangleRenderer(World* world, GameObject* go, std::istream& fin)
{
	std::string tmp;
	int w, h, r, g, b, a;

	fin.ignore(100, '[');
	fin >> w >> h;
	fin.ignore(100, ']');
	fin.ignore(100, '[');
	fin >> r >> g >> b >> a;
	fin.ignore(100, ']');
	
	if (world->numActiveRectangleRenderers == MAX_OBJECTS - 1)
		return;
	else
	{
		world->rectangleRenderers[world->numActiveRectangleRenderers] = RectangleRenderer(w, h, Color(r, g, b, a));
		go->CreateRenderer(&world->rectangleRenderers[world->numActiveRectangleRenderers]);
		world->numActiveRectangleRenderers++;
	}
}

void World::AddRectangleCollider(World* world, GameObject* go, std::istream& fin)
{
	if (world->numActiveRectangleColliders == MAX_OBJECTS - 1)
		return;
	else
	{
		world->rectangleColliders[world->numActiveRectangleColliders] = RectangleCollider();
		go->CreateCollider(&world->rectangleColliders[world->numActiveRectangleColliders]);
		world->numActiveRectangleColliders++;
	}
}

void World::AddCollisionColorChanger(World* world, GameObject* go, std::istream& fin)
{
	if (world->numActiveColorChangers == MAX_OBJECTS - 1)
		return;
	else
	{
		world->collisionColorChangers[world->numActiveColorChangers] = CollisionColorChanger();
		go->CreateColliderColorChanger(&world->collisionColorChangers[world->numActiveColorChangers]);
		world->numActiveColorChangers++;
	}
}

void World::SaveLevel(std::string filename) 
{
	std::ofstream fout;
	fout.open(filename);
	for (int i = 0; i < numActiveObjects; i++)
	{
		GameObject go = gameObjects[i];
		fout << go.GetName() << " ";
		//transform position
		fout << "[" << go.GetTransform()->position.x << " " << go.GetTransform()->position.y << "]";

		//iterate through each possible component (lol)
		if (go.GetCollider() != nullptr)
		{
			fout << " " << CompId::ColliderId;
		}

		if (go.GetPlayerController() != nullptr) 
		{
			fout << " " << CompId::PlayerControllerId;
		}
		if (go.GetCollisionColorChanger() != nullptr)
		{
			fout << " " << CompId::ColorChangerId;
		}
		if (go.GetRenderer() != nullptr)
		{
			fout << " " << CompId::RendererId;
			fout << " [" << go.GetRenderer()->width << " " << go.GetRenderer()->height << "]";
			fout << " [" << go.GetRenderer()->color.r << " " << go.GetRenderer()->color.g << " "
				<< go.GetRenderer()->color.b << " " << go.GetRenderer()->color.a << "]";
		}
		fout << std::endl;

	}
}


void World::LoadLevel(std::string fileName)
{
	std::ifstream fin;
	std::string tmp;

	componentMap[CompId::ColliderId] = AddRectangleCollider;
	componentMap[CompId::RendererId] = AddRectangleRenderer;
	componentMap[CompId::PlayerControllerId] = AddPlayerController;
	componentMap[CompId::ColorChangerId] = AddCollisionColorChanger;

	fin.open(fileName);

	while (!fin.eof())
	{
		std::getline(fin, tmp);
		
		if (tmp != "")
		{
			if ((tmp[0] != '/' && tmp[1] != '/'))
			{
				std::istringstream line(tmp);
				ReadLine(line);
			}
		}
	}
	fin.close();
	componentMap.clear();
}

void World::ReadLine(std::istream& line)
{
	std::string tmp, name;
	int x, y, id;

	line >> name;
	//std::cout << "name " << name << std::endl;
	line.ignore(100, '[');
	line >> x >> y >> tmp;
	GameObject* obj = LoadGameObject(name, Transform(Vector2(x, y)));
	line >> id;
	while (!line.eof())
	{
		//line >> id;
		componentMap[id](this, obj, line);
		//line.ignore('\n');
		line >> id;
	}
}