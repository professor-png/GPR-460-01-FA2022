#pragma once

//#include "EngineState.h"
struct EngineState;
class GameObject;

class PlayerController
{
private:
	int speed = 10;

public:
	PlayerController();
	~PlayerController();

	void ShutDown();
	void Update(EngineState* engine);
	static void Update(PlayerController* player, EngineState* engine);
	GameObject* owner = nullptr;
};